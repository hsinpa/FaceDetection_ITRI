#pragma once




#include "stdint.h"


#ifndef	__FV_COMMON_DEF_H__
#define __FV_COMMON_DEF_H__


namespace FV_ADV
{
	
	

	
	enum Preference_ex
	{
		fv_EX_PREFER_NONE = 0,						           //!< None.
		fv_EX_PREFER_HARDWARE_DETECTION = (1 << 1),	           //!< Prefers GPU hardware acceleration on face detection.
		fv_EX_PREFER_FAST_DETECTION = (1 << 2),		           //!< Prefers non-DNN algorithm for faster face detection speed.
		fv_EX_PREFER_HARDWARE_EXTRACTION = (1 << 3),	           //!< Prefers GPU hardware acceleration on face extraction.
		fv_EX_PREFER_FAST_EXTRACTION = (1 << 4),		           //!< Reserved for future use.
		fv_EX_PREFER_INTEL_MOVIDIUS_VPU_DETECTION = (1 << 5),	   //!< Prefers Intel Movidius VPU acceleration on face detection.
		fv_EX_PREFER_INTEL_MOVIDIUS_VPU_EXTRACTION = (1 << 6),   //!< Prefers Intel Movidius VPU acceleration on face extraction.
		fv_EX_PREFER_INTEL_MOVIDIUS_VPU_HDDL = (1 << 7)		   //!< Prefers Intel Movidius VPU acceleration with HDDL plugin.
	};

	enum Preference_option
	{
		fv_PREFER_NONE = 0,						           //!< None,use cpu.
		fv_PREFER_GPU_Accelerate,	           //!< Prefers GPU hardware acceleration on face detection.
		fv_PREFER_FAST_DETECTION,		           //!< Prefers non-DNN algorithm for faster face detection speed.
		fv_PREFER_INTEL_MOVIDIUS_VPU,	   //!< Prefers Intel Movidius VPU acceleration on face detection.
		fv_PREFER_INTEL_MOVIDIUS_VPU_HDDL		   //!< Prefers Intel Movidius VPU acceleration with HDDL plugin.
	};

	enum InstanceType
	{
		Type_Recognizer = 0,
		Type_UserAction,
		Type_QualityDetector


	};

	enum Err_code
	{


		Err_RETURN_ASYNC = 2,						//!< Async operation.
		Err_RETURN_FALSE = 1,						//!< False.
		Err_OK = 0,							//!< Succeeded.
		Err_FAIL = -1,						//!< Failed.
		Err_OUT_OF_MEMORY = -2,				//!< Out of memory error.
		Err_NOT_IMPLEMENT = -3,				//!< Not implement error.
		Err_INVALID_ARGUMENT = -4,			//!< Invalid argument error.
		Err_INDEX_OUT_OF_RANGE = -5,			//!< Index out of range error.
		Err_UNEXPECTED = -6,					//!< Unexpected error.
		Err_INCONSISTENT_VERSION = -7,		//!< Inconsistent data structure version error.
		Err_NOT_INIT = -8,					//!< Not initialize error.
		Err_CONFIG_ERROR = -9,				//!< Configuration error.
		Err_NOT_FOUND = -10,					//!< Not found error.
		Err_NOT_SUPPORT = -11,				//!< Not support error.

		Err_FEATURE_SIZE_MISMATCH = -30,		//!< Feature size mismatch.
		Err_DATABASE_ERROR = -31,				//!< Database access error.
		Err_FEATURE_INCOMPLETE = -32,			//!< Feature extract incomplete for add
		Err_DATABASE_COLLECTION_EXCEEDED = -33, //!< Collection count in database is exceeded.
		Err_DATABASE_ENCRYPTION_INVALID_SETTING = -34, //!< Database password is not match certain rules.
		Err_DATABASE_ENCRYPTION_INCORRECT_PASSWORD = -35,	//!< Database password is incorrect.
		Err_DATABASE_ENCRYPTION_INVALID_DATABASE_DATA = -36, //!< Database cannot change to enable/disable encryption setting when any record exists.

		Err_UNKNOWN_HOST = -40,				//!< Unknown license server.
		Err_NETWORK_ERROR = -41,				//!< Network issue while communicate with license server.
		Err_LICENSE_FAIL = -42,				//!< License is failed.
		Err_LICENSE_EXPIRED = -43,			//!< License is expired.
		Err_LICENSE_ACTIVATION_EXCEEDED = -44,//!< License activation is exceeded.
		Err_LICENSE_NOT_SUPPORT = -45,		//!< License feature is not support.
		Err_LICENSE_CONSTRAIN_HARDWARE = -46,	//!< License hardware is constrained.
		Err_LICENSE_SERVER_ERROR = -47,		//!< License server error.
		Err_LICENSE_INVALID_PACKAGE_NAME = -48, //!< License is restricted with specific package name for Android, or bundleId for iOS.
		Err_LICENSE_INCORRECT_KEY = -49,		//!< License key is incorrect.

		Err_RUNTIME_FILE_NOT_COMPLETE = -50,  //!< FaceMe runtime files are not complete.
		Err_INFERENCE_ENGINE_NOT_SUPPORT = -51, //!< Inference engine is not support.

		Err_LICENSE_INCORRECT_PLATFORM = -60,	//!< License is not authorized on current platform.
		Err_LICENSE_PERIOD_NOT_START = -61,	//!< License period does not start yet.

		Err_RECOGNIZE_IMAGE_PROCESSING_EXCEEDED = -70, //!< Recognize fps is exceeded.

		Err_LICENSE_NEED_ACTIVATION_URL = -140,	//!< License needs to use alternate link activation.
		Err_LICENSE_URL_CODE_INCORRECT = -141,	//!< The 6-digit license activation code is incorrect.
		Err_LICENSE_URL_CODE_EXPIRED = -142,		//!< The 6-digit license activation code is expired. Please try again.
		Err_LICENSE_URL_CODE_RETRY_EXCEEDED = -143, //!< Retry too many times. Please wait awhile and then try again.


		//detail for Err_NOT_INIT(-8)
		Err_NOT_INST_RECOGNIZE = -810,
		Err_NOT_INST_DATAMANAGER = -811,
		Err_NOT_INST_USERACTION = -812,
		Err_NOT_INST_QUALITY = -813,
		Err_NOT_INST_LICENSE = -814,

		//detail for Err_NOT_INIT(-8)
		Err_NOT_INIT_RECOGNIZE = -820,
		Err_NOT_INIT_DATAMANAGER = -821,
		Err_NOT_INIT_USERACTION = -822,
		Err_NOT_INIT_QUALITY = -823,
		Err_NOT_INIT_LICENSE = -824,


		Err_SetMinFace_fail = 11,
		Err_SetMaxFace_fail = 12,
		Err_SetOrder_fail = 13,
		Err_SetPrecision_fail = 14 ,
		Err_FaceInfo_cfg = 15,
		Err_FaceAttr_cfg = 16,
		Err_FaceFeature_cfg = 17,
		Err_FaceLandmark_cfg = 18,





		Err_SDK_Fail = 98,
		Err_Already_init = 99,
		Err_NullPtr = 101

	};


	enum Err_code_license
	{
		Err_L_Register = 50,
		Err_L_Deactive,
		Err_L_Renew
	};
}


#endif // __FV_COMMON_DEF_H__
