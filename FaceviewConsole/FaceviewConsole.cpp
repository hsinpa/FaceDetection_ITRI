// FaceviewConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "asio.hpp"
#include "./SocketHelper.h";
#include <iostream>
#include "./DeviceEnumerator.h";
#include "./FaceViewModel.h";
#include "./cv_show_images.h";

//FaceView SDK
#include "fv.h";
#include "common_def.h";
#include "base_def.h";
#include "fv_face.h";

//OpenV API
#include "opencv2/opencv.hpp";
#include "opencv2/core.hpp";
#include "opencv2/imgcodecs.hpp";
#include "opencv2/highgui.hpp";
#include <opencv2/core/types_c.h>

# include <conio.h>
#include <curl/curl.h>
#include <atlstr.h>
#include "StaticText.h"
#include <json.hpp>

using json = nlohmann::json;
using namespace cv;
using namespace FV_ADV;

VideoCapture cap;
bool isRun = true;

const std::string save_image_file_name = "save_file.jpg";
const std::vector<std::string> szEmotion = { "N/A", "happy", "surprised", "sad", "angry", "neutral" };
const std::vector<std::string> szGender  = { "N/A", "male", "female" };

std::shared_ptr<SocketHelper> _socketHelper;
std::shared_ptr<asio::io_context> _io_context;
std::shared_ptr<asio::ip::tcp::socket> _socket;
std::shared_ptr < FaceViewModel> _faceViewModel;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


void PerformInputRouter(bool show_hint = false) {
    if (show_hint)
        std::cout << "Keyboard Action => 1 : Take Temp Picture, 2 : Save Picture, 3 : Compare Save and Temp picture " << std::endl;

    char ch;
    ch = _getch();

    std::cout << "Process input " << ch << std::endl;

    if (ch == '1') {

    }

    if (ch == '2') {

    }

    //Loop if not 3
    if (ch != '3') {
        PerformInputRouter();
    }
}

std::vector<UserFaceItem> recogPicture(std::string name, Mat image, bool debug_flag = false)
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

void compare_texture_similarity(std::string source_img_path, std::string target_img_path) {
    Mat source_image = imread(source_img_path);
    Mat target_image = imread(target_img_path);
    float score = 0.0;

    if (!source_image.empty() && !target_image.empty())
    {
        std::vector<UserFaceItem> sourceInfos = recogPicture("source_image", source_image);
        std::vector<UserFaceItem> targetInfos = recogPicture("target_image", target_image);

        fv_FaceFeature a = sourceInfos[0].faceFeature;
        fv_FaceFeature b = targetInfos[0].faceFeature;

        auto ret = FV_CompareFaces(&a, &b, &score);

        std::cout << "source " + source_img_path << std::endl;
        std::cout << "target " + target_img_path << std::endl;
        std::cout << "Score: " << score << std::endl;

        ShowManyImages("Targets", 2, source_image, target_image);
    }
}

std::string compare_texture_similarity(std::string source_img_path) {
    Mat source_image = imread(source_img_path);
    std::string similar_user_id = "";
    float score = 0.0;
    float highest_score = 0.0;

    if (!source_image.empty())
    {
        std::vector<UserFaceItem> sourceInfos = recogPicture("source_image", source_image);
        fv_FaceFeature a = sourceInfos[0].faceFeature;

        auto user_list = _faceViewModel->get_users();

        for (std::string bind_id : user_list) {
            UserFaceItem compare_item = _faceViewModel->get_face(bind_id);
            fv_FaceFeature b = compare_item.faceFeature;

            auto ret = FV_CompareFaces(&a, &b, &score);

            std::cout << "Score: " << bind_id << ", " << score << std::endl;

            if (score >= MIN_COMPARE_THRESHOLD && score > highest_score) {
                highest_score = score;
                similar_user_id = compare_item.name;
            }
        }
    }

    return similar_user_id;
}

void on_socket_data_receive(std::string data) {
    std::cout << "FaceviewConsole read " << data << std::endl;
    srand((unsigned int)time(NULL));

    if (data != "") {

            json json_data = json::parse(data);

            std::string action_name = json_data["action"].get<std::string>();
            std::cout << "Action " << action_name << std::endl;

            std::string source_path = json_data["source_path"].get<std::string>();
            std::cout << "Source " << source_path << std::endl;

            std::string ticket_id = json_data["ticket_id"].get<std::string>();
            std::cout << "Ticket " << ticket_id << std::endl;

            json send_msg_json;
            send_msg_json["action"] = action_name;
            send_msg_json["ticket_id"] = ticket_id;

            if (action_name == SOCKET_ACTION_REGISTER) {
                auto return_id = _faceViewModel->command_register_user(source_path);
                send_msg_json["id"] = return_id;

                _socketHelper->send(_socket, send_msg_json.dump());
            }

            if (action_name == SOCKET_ACTION_DETECTION) {
                std::string detect_id = compare_texture_similarity(source_path);
                std::cout << "Compare Result " << detect_id << std::endl;
                send_msg_json["id"] = detect_id;

                _socketHelper->send(_socket, send_msg_json.dump());
            }

            _socketHelper->sock_accept(_socket, on_socket_data_receive);
            _io_context->run();
        }
        else {
            _socket->close();
            _io_context->stop();
        }

}

int main()
{
    srand((unsigned int)time(NULL));

    _faceViewModel = std::make_shared<FaceViewModel>();
    std::string ver = "";
    FV_GetVersionInto(&ver);

    CURL* easy_handle = curl_easy_init();
    std::cout << "FV_GetVersionInto " << ver << std::endl;

    Inst* m_Sdk_Ptr = FV_GetInstance();

    std::string moduledir_path = FaceViewModel::get_module_name();

    std::cout << "FV_SysConfig Path " << moduledir_path.data() << std::endl;

    HRESULT SysConfig_res = FV_SysConfig(moduledir_path.data());

    std::cout << "SysConfig_res " << SysConfig_res << std::endl;

    int res = 0;
//
#ifdef _HWK_
    res = FV_HWKey();
#else
    std::string key_string = "8cJOzharg4hYzXcDX2SGT3QL1XVzeCQuAIeHDBhC";
    res = FV_SWKey((const UCHAR*)key_string.data(), (uint16_t)strlen(key_string.data()));
#endif
//
    HRESULT key_result = FV_KeyStart();
    std::cout << "License Res " << key_result << std::endl;
//
    //HRESULT default_params_result = FV_UseDefaultParams();
    FV_MinFace(10);
    FV_DetectionOutputOrder(fv_ORDER_CONFIDENCE);
    FV_ThresholdLevel(precision::lvlE4);

    int32_t extract_option = FEATURE_OPTION_BOUNDING_BOX | FEATURE_OPTION_FEATURE | FEATURE_OPTION_EMOTION | FEATURE_OPTION_AGE | FEATURE_OPTION_GENDER;
    HRESULT extract_r = FV_ExtractOption(extract_option);
    std::cout << "FV_ExtractOption " << extract_r << std::endl;

    HRESULT recognizeConfig_r = FV_RecognizeConfig(fv_PREFER_NONE, fv_e_LEVEL_DEFAULT, 0, fv_e_LEVEL_VH_M, 0);
    std::cout << "FV_RecognizeConfig " << recognizeConfig_r << std::endl;

    HRESULT initial_r = FV_InitialSDK();
    std::cout << "FV_InitialSDK " << initial_r << std::endl;

    HRESULT applyEngine_r = FV_ApplyEngine();
    std::cout << "FV_ApplyEngine " << applyEngine_r << std::endl;

    //PerformInputRouter(true);
    //DeviceEnumerator::printDebugInfo();

    std::string source_img_path = moduledir_path + "\\texture_assets\\elon_musk_02.jpg";
    std::string target_img_path = moduledir_path + "\\texture_assets\\elon_musk_02.jpg";

    std::thread socket_thread = std::thread([]() {
        _socketHelper = std::make_shared<SocketHelper>();
        _io_context = std::make_shared<asio::io_context>();
        _socket = std::make_shared<asio::ip::tcp::socket>(*_io_context);

        auto socket_acceptor = _socketHelper->create_server(_io_context, _socket, 5015);
        _socketHelper->sock_accept(_socket, on_socket_data_receive);
        _io_context->run();
    });

    //auto return_id = _faceViewModel->command_register_user(source_img_path);
    //std::cout << "ID " << return_id << std::endl;
    //compare_texture_similarity(source_img_path, target_img_path);

    //auto user_list = _faceViewModel->get_users();
    //for (std::string bind_id : user_list) {
    //    _faceViewModel->get_face(bind_id);
    //}
    //auto compare_id = compare_texture_similarity(target_img_path);
    //std::cout << "Compare Result " << compare_id << std::endl;

    PerformInputRouter(true);

    HRESULT finalizeSDK_r = FV_FinalizeSDK();
    std::cout << "FV_FinalizeSDK " << finalizeSDK_r << std::endl;

    return res;
}