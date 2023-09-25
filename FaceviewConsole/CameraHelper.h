#pragma once

#include "fv.h";
#include "common_def.h";
#include "base_def.h";
#include "fv_face.h";

#include "opencv2/opencv.hpp";
#include "opencv2/core.hpp";
#include "opencv2/imgcodecs.hpp";
#include "opencv2/highgui.hpp";
#include <opencv2/core/types_c.h>

using namespace cv;

class CameraHelper
{
private:
	VideoCapture _cap;
	std::shared_ptr<cv::Mat> frame;

public :
	std::shared_ptr<cv::Mat> TakeWebcamTex(int device_index);
	std::shared_ptr<cv::Mat> ReadFilePathTex(std::string file_path);

};

