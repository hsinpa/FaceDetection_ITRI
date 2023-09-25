#include "CameraHelper.h"

std::shared_ptr<cv::Mat> CameraHelper::TakeWebcamTex(int device_index) {
	if (_cap.open(device_index + CAP_DSHOW)) {
		int timestamp = 0;

		_cap.read(*frame);

		return frame;
	}

	return nullptr;
}



