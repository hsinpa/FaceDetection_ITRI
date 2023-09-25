#pragma once
#include <string>
#include <cstddef>
#include <fv_face.h>
#include "base_def.h"

#include "opencv2/opencv.hpp";
#include "opencv2/core.hpp";
#include "opencv2/imgcodecs.hpp";
#include "opencv2/highgui.hpp";
#include <Windows.h>
#include <atlstr.h>

using namespace cv;

class FaceViewModel
{

private:
	std::map<std::string, std::shared_ptr<UserFaceItem>> _face_cache;

public:
	const std::string FAIL_CODE = "-1";

	static std::string get_module_name();
	static std::string gen_rand_string(int lens);
	static std::string encodeFloat(float data[], int sz);
	static void float2Bytes(float val, byte* bytes_array);
	static float bytes2Float(byte b0, byte b1, byte b2, byte b3);
	static FV_ADV::_FeatureData decodeFloat(std::string encoded_string);

	FaceViewModel();
	std::string command_register_user(std::string file_path);
	std::vector<UserFaceItem> recog_picture(std::string name, Mat& image, bool debug_flag = false);

	std::string save_user(UserFaceItem userFaceItem, const cv::Mat& img);
	void get_user(std::string bindID);

	std::vector<std::string> get_users();
	void delete_user(std::string bindID);
	UserFaceItem get_face(std::string bindID);
};

