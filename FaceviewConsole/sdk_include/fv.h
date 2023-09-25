#pragma once

#include <windows.h>

#include "stdio.h"
#include "stdlib.h"

#include <string>


#include "common_def.h"
#include "base_def.h"
#include "fv_face.h"


#include <opencv2/opencv.hpp>




#ifdef FV_EXPORTS
#define DLLIMPORT __declspec (dllexport)
//#define TESTDLL2012_API __declspec(dllexport)
#else
//#define TESTDLL2012_API __declspec(dllimport)
#define DLLIMPORT __declspec (dllimport)
#endif



#define FV_INIT_STRUCT(ptr, class_name) { std::memset((uint8_t *)ptr, 0, sizeof(class_name)); (*ptr).sizeOfStructure = sizeof(class_name); }



namespace FV_ADV
{


	class Inst
	{
	public:
		Inst();
		DLLIMPORT ~Inst();	
	};
}

using namespace FV_ADV;


DLLIMPORT HRESULT FV_GetVersionInto(std::string *info);
DLLIMPORT Inst* FV_GetInstance();
DLLIMPORT void FV_CreateInstance();




DLLIMPORT HRESULT FV_InitialSDK();
DLLIMPORT HRESULT FV_FinalizeSDK();

DLLIMPORT HRESULT FV_SysConfig(const char* bundle_path);

#ifdef _HWBUNDLEKEY_
DLLIMPORT HRESULT FV_HWKey();
#else
DLLIMPORT HRESULT FV_SWKey(const unsigned char *keydata, uint16_t len);
#endif

DLLIMPORT HRESULT FV_KeyStart();
DLLIMPORT HRESULT FV_KeyDeactive();
DLLIMPORT HRESULT FV_KeyRenew();
DLLIMPORT HRESULT FV_GetAllowModel(std::string *data);
DLLIMPORT HRESULT FV_UseDefaultParams();

//new
DLLIMPORT HRESULT FV_GetGPUEnabled(bool& enable);//if NV GPU hardware is enabled



DLLIMPORT HRESULT FV_ThresholdLevel(int32_t level);
DLLIMPORT HRESULT FV_DetectionOutputOrder(uint32_t order);
DLLIMPORT HRESULT FV_ExtractOption(int32_t option);//age gender emotion landmark


DLLIMPORT HRESULT FV_MinFace(uint32_t width);
DLLIMPORT HRESULT FV_MaxFace(uint32_t width);
DLLIMPORT HRESULT FV_ApplyEngine();//  FV_InitEngine setconfig



DLLIMPORT HRESULT FV_DetectBatchsize(uint32_t num);
DLLIMPORT HRESULT FV_ExtractBatchsize(uint32_t num);
DLLIMPORT HRESULT FV_MaxFrame(uint32_t w, uint32_t h);


//new
DLLIMPORT HRESULT FV_InputMode(uint32_t mode); //// 0: image, 1: video
DLLIMPORT HRESULT FV_GPUID(uint8_t gpuid);// default 0, start from 0

										  //new
DLLIMPORT HRESULT FV_DetectQulity_Prefer(int32_t value);//refer to fv_QC_PREFERENCE



DLLIMPORT HRESULT FV_RecognizeConfig(uint32_t prefer_exvalue, int32_t detect_level, uint16_t detect_threads, int32_t extract_level, uint16_t extract_threads);
DLLIMPORT HRESULT FV_RecognizeConfig_op(int32_t prefer_option, int32_t detect_level, uint16_t detect_threads, int32_t extract_level, uint16_t extract_threads);




DLLIMPORT HRESULT FV_GetMinFace(uint32_t *value);
DLLIMPORT HRESULT FV_GetMaxFace(uint32_t *value);
DLLIMPORT HRESULT FV_GetOutputOrder(uint32_t *value);
DLLIMPORT HRESULT FV_GetThresholdValue(float *value);


DLLIMPORT HRESULT FV_ExtractNumberOfFace(cv::Mat image, uint32_t *number);

//new
DLLIMPORT HRESULT FV_ExtractNumberOfFaces(cv::Mat* images,uint32_t arrysize, uint32_t* facecounts);


DLLIMPORT HRESULT FV_GetFaceExtractedInfo(uint32_t number, std::vector<UserFaceItem> *pFaceRecognizedInfos);
DLLIMPORT HRESULT FV_CompareFaces(const fv_FaceFeature *compare_faceFeatureA, const fv_FaceFeature *compare_faceFeatureB, float *confidence);


DLLIMPORT HRESULT FV_DetectQuality(cv::Mat image, const fv_QualityDetectConfig *config, fv_QualityDetectResult *result);

