#include "FaceViewModel.h"
#include <json.hpp>
#include "StaticText.h"
#include "base64.h"
#include <fv.h>
#include <fstream>
#include "HttpRequest.h"

using json = nlohmann::json;


FaceViewModel::FaceViewModel() {
}

#pragma region Static Function
std::string FaceViewModel::get_module_name() {
    CString path;
    GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
    path.ReleaseBuffer();
    int pos = path.ReverseFind('\\');
    path = path.Left(pos);

    std::string moduledir_path(CW2A(path.GetString()));
    return moduledir_path;
}

std::string FaceViewModel::gen_rand_string(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

std::string FaceViewModel::encodeFloat(float data[], int sz) {
    byte bytes[8192];
    std::string encoded_b64_strings;
    for (int i = 0; i < sz; i++) {
        float float_example = data[i];
        float2Bytes(float_example, &bytes[i * 4]);
    }
    std::string encoded = base64_encode(bytes, sz * 4);

    return encoded;
}


void FaceViewModel::float2Bytes(float val, byte* bytes_array) {
    // Create union of shared memory space
    union {
        float float_variable;
        byte temp_array[4];
    } u;
    // Overite bytes of union with float variable
    u.float_variable = val;
    // Assign bytes to input array
    memcpy(bytes_array, u.temp_array, 4);
}

float FaceViewModel::bytes2Float(byte b0, byte b1, byte b2, byte b3) {
    float f;
    uchar b[] = { b0, b1, b2, b3 };
    memcpy(&f, &b, sizeof(f));
    return f;
}

FV_ADV::_FeatureData FaceViewModel::decodeFloat(std::string encoded_string) {
    std::string decoded = base64_decode(encoded_string);
    std::vector<uchar> faceByte(decoded.begin(), decoded.end());
    FV_ADV::_FeatureData fD;
    fD.size = faceByte.size() / 4;
    for (int i = 0; i < fD.size; i++) {

        fD.data[i] = bytes2Float(faceByte[(i * 4)], faceByte[(i * 4 + 1)], faceByte[(i * 4 + 2)], faceByte[(i * 4 + 3)]);
    }
    return fD;
}
#pragma endregion

#pragma region Faceview Query
std::string FaceViewModel::save_user(UserFaceItem userFaceItem, const cv::Mat& img) {
    //convert image to base64 string
    std::vector<uchar> buf;
    cv::imencode(".jpg", img, buf);
    auto base64_jpg = reinterpret_cast<const unsigned char*>(buf.data());
    std::string picture_b64 = base64_encode(base64_jpg, buf.size());
    int have_same = 0;
    auto facedata = encodeFloat(userFaceItem.faceFeature.featureData.data, userFaceItem.faceFeature.featureData.size);

    std::string visit_id = gen_rand_string(12);
    std::cout << "visit_id: " << visit_id << "\n";

    json curl_request = {
        {"Bindid", visit_id},
        {"alias", visit_id},
        {"facedata", facedata},
        {"facetype", std::to_string(userFaceItem.faceFeature.featureType) },
        {"subtype", std::to_string(userFaceItem.faceFeature.featureSubType) },
        {"f_size", std::to_string(userFaceItem.faceFeature.sizeOfStructure) },

        {"picture", picture_b64 },
        {"apvalue", std::to_string(0) },
        {"apstring", ""}
    };

    auto headers = std::vector<std::string>{ HEADER_JSONTYPE };

    return HttpRequest::Curl(HTTP_ADD_USER, HTTPMETHOD_POST, headers, curl_request);
}

std::string FaceViewModel::command_register_user(std::string file_path) {
    std::ifstream f(file_path);

    if (!f.good()) return this->FAIL_CODE;

    Mat source_image = imread(file_path);

    auto userfaces = recog_picture("user_face", source_image);

    if (userfaces.size() <= 0) return this->FAIL_CODE;

    std::string save_result = save_user(userfaces[0], source_image);

    unsigned first = 4;
    unsigned last = save_result.find(" done");

    return save_result.substr(first, last - first);
}

std::vector<UserFaceItem> FaceViewModel::recog_picture(std::string name, Mat& image, bool debug_flag)
{
    std::vector<UserFaceItem> faceRecognizedInfos;
    faceRecognizedInfos.clear();

    //std::vector<_FaceRecognizedInfo> ss;
    uint32_t num = 0;
    int ret = FV_ExtractNumberOfFace(image, &num);

    if (num < 1)
        return faceRecognizedInfos;

    ret = FV_GetFaceExtractedInfo(num, &faceRecognizedInfos);
    int length = (int)faceRecognizedInfos.size();

    if (debug_flag) {
        namedWindow(name, WINDOW_AUTOSIZE);// Create a window for display.
        cv::imshow(name, image);
        cv::waitKey(15);
    }

    return faceRecognizedInfos;
}


UserFaceItem FaceViewModel::get_face(std::string bindID) {
    if (_face_cache.contains(bindID)) {
        return *_face_cache[bindID];
    }

    auto headers = std::vector<std::string>{  };
    json empty_json = {};
    UserFaceItem temp;

    std::string url = std::format("http://localhost:2211/FV/DBService/ReadRecord_faces/{}", bindID);
    auto json_result = json::parse(HttpRequest::Curl(url, HTTPMETHOD_GET, headers, empty_json));
    auto json_face_data = json_result["data"]["Data"][0][0];

    temp.faceFeature.featureData = decodeFloat(json_face_data["facedata"].get<std::string>());
    temp.faceFeature.featureSubType = json_face_data["facesubtype"].get<int>();
    temp.faceFeature.featureType = json_face_data["facetype"].get<int>();
    temp.faceFeature.sizeOfStructure = json_face_data["fsize"].get<int>();
    temp.name = bindID;

    _face_cache.insert({ bindID, std::make_shared<UserFaceItem>(temp) });

    return temp;
}

std::vector<std::string> FaceViewModel::get_users() {
    auto headers = std::vector<std::string>{  };
    std::vector<std::string> user_list;
    json empty_json = {};

    auto json_result = json::parse( HttpRequest::Curl(HTTP_GET_USERS, HTTPMETHOD_GET, headers, empty_json));
    auto json_data_array = json_result["data"];

    for (auto& element : json_data_array) {
        std::string bind_id = element.get<std::string>();

        user_list.push_back(bind_id);
    }

    return user_list;
}
#pragma endregion
