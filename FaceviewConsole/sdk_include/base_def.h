#pragma once
#include "stdint.h"
//#include <opencv2/opencv.hpp>
namespace FV_ADV
{
	

	enum precision 
	{
		lvlE6 = 0,
		lvlE5,
		lvlE4,
		lvlE3,
		lvlE2
	};
	enum output_order
	{
		fv_NO_ORDER = 0,		//!< No order.
		fv_ORDER_CONFIDENCE,	    //!< Confidence. 
		fv_ORDER_FACE_WIDTH		//!< Face width.
	};
	
	

	/**
	*  Speed level for detection model
	*/
	enum fv_detection_lvl
	{
		fv_d_LEVEL_DEFAULT = 0,		//!< Default.
		fv_d_LEVEL_HIGH,			//!< High.   (( DDN
		fv_d_LEVEL_ULTRA_HIGH		//!< Ultra-High. (( DDN-X

	};

	/**
	* Speed level for extraction model.
	*/
	enum fv_extraction_lvl
	{
		fv_e_LEVEL_DEFAULT = 0,	//!< Default.
		fv_e_LEVEL_STANDARD,		//!< Standard.
		fv_e_LEVEL_HIGH,			//!< High.
		fv_LEVEL_ULTRA_HIGH,		//!< Ultra-High.
		fv_LEVEL_HIGH_ASIAN,		//!< High for Asian.
		fv_e_VERY_HIGH,		//!< Very-High.
		fv_e_LEVEL_H3,
		fv_e_LEVEL_UH3,
		fv_e_LEVEL_UH3_M, 	        //!< 3rd generation of Ultra-High with mask.
		fv_e_LEVEL_VH_M, 	        //!< Very-High with mask.
		fv_e_LEVEL_H5,		        //!< 5th generation of High.
		fv_e_LEVEL_UH5, 	        //!< 5th generation of Ultra-High.
		fv_e_LEVEL_UH5_M, 	        //!< 5th generation of Ultra-High with mask.
		fv_e_LEVEL_VH5, 	        //!< 5th generation of Very-High.
		fv_e_LEVEL_VH5_M 	        //!< 5th generation of Very-High with mask.

	};

	
	
	enum fv_EMOTION
	{
		fv_EMOTION_UNKNOWN = 0,	//!< Unknown.
		fv_EMOTION_HAPPY,		//!< happy.
		fv_EMOTION_SURPRISED,	//!< Surprised.
		fv_EMOTION_SAD,			//!< Sad.
		fv_EMOTION_ANGRY,		//!< Angry.
		fv_EMOTION_NEUTRAL,		//!< Neutral.
	};

	enum fv_GENDER
	{
		fv_GENDER_UNKNOWN = 0,	//!< Unknown.
		fv_GENDER_MALE,			//!< Male.
		fv_GENDER_FEMALE		//!< Female.
	};


	enum fv_USER_ACTION
	{
		UA_DETECT_NONE = 0,			//!< None.
		UA_DETECT_BLINK_EYES,		//!< Blink eye detection.
		UA_DETECT_TURN_HEAD,		//!< Turn head detection.
		UA_DETECT_SMILE,			//!< Smile detection.
		UA_DETECT_OPEN_MOUTH,		//!< Open mouth detection.
		UA_DETECT_NOD_HEAD,			//!< Nod head detection.
		UA_DETECT_LIFT_EYE_BROWS,	//!< Lift eye brows detection.
		UA_DETECT_CENTER			//!< Detect if the face is in the center of the image.
	};

	enum fv_FEATURE_OPTIONS
	{
		
		FEATURE_OPTION_NONE = 0,									//!< None.
		FEATURE_OPTION_BOUNDING_BOX = (1LL << 1),				//!< Extract Bounding box.
		FEATURE_OPTION_FEATURE_LANDMARK = (1LL << 2),			//!< Extract Feature Landmark.
		FEATURE_OPTION_FEATURE = (1LL << 3),						//!< Extract Feature.
		FEATURE_OPTION_EMOTION = (1LL << 4),						//!< Extract Emotion.
		FEATURE_OPTION_AGE = (1LL << 5),							//!< Extract Age.
		FEATURE_OPTION_GENDER = (1LL << 6),						//!< Extract Gender.
		FEATURE_OPTION_POSE = (1LL << 7),						//!< Extract Pose.
		FEATURE_OPTION_OCCLUSION = (1LL << 0),					//!< Extract Occlusion.
		FEATURE_OPTION_MASKED_FEATURE = (1LL << 8),				//!< Extract Masked Feature.
		FEATURE_OPTION_FULL_FEATURE = ((1LL << 3) | (1LL << 8)),	//!< Extract Full Feature.
		FEATURE_OPTION_ALL = INT32_MAX						//!< Extract All.
	};

	enum fv_mask_state {
		fv_mask_disappear = 0,
		fv_mask_incorrect,
		fv_mask_ok
	};

	enum fv_QUALITY_CHECK_MODE
	{
		QUALITY_CHECK_MODE_ONE_FAILURE,  //!< Return when one detect type fails.
		QUALITY_CHECK_MODE_ALL_FAILURE   //!< Return when all detect types are checked.
	};


	enum fv_BLUR_QUALITY_MODE
	{
		BLUR_CAMERA_MODE = 0,    //!< Image.
		BLUR_WEBCAM_MODE         //!< Video.
	};

	enum fv_QUALITY_ISSUE_OPTIONS
	{
		QUALITY_ISSUE_OPTION_NONE = 0,                  //!< None.
		QUALITY_ISSUE_OPTION_UNDERSIZED = 1,            //!< Check if the face is too small.
		QUALITY_ISSUE_OPTION_OCCLUDED = (1LL << 1),     //!< Check if the face is occluded.
		QUALITY_ISSUE_OPTION_BLUR = (1LL << 2),         //!< Check if the photo is blurred.
		QUALITY_ISSUE_OPTION_EXPOSURE = (1LL << 3),     //!< Check lighting.
		QUALITY_ISSUE_OPTION_EYE_CLOSED = (1LL << 4),   //!< Check if eyes are closed.
		QUALITY_ISSUE_OPTION_WRONG_ANGLE = (1LL << 5),  //!< Check face angle.
		QUALITY_ISSUE_OPTION_GRAYSCALE = (1LL << 6),    //!< Check if the image is grayscale.
		QUALITY_ISSUE_OPTION_ALL = INT32_MAX            //!< Check all.
	};

	enum fv_OCCLUSION_FAIL_REASON
	{
		
		OCCLUSION_NONE = 0,              //!< None.
		OCCLUSION_UNKNOWN = (1LL << 1),  //!< The face is not suitable for occlusion detection.
		OCCLUSION_LEFTEYE = (1LL << 2),     //!< The face is occluded by left eye.
		OCCLUSION_RIGHTEYE = (1LL << 3),     //!< The face is occluded by right eye.
		OCCLUSION_NOSE = (1LL << 4),     //!< The face is occluded by nose.
		OCCLUSION_MOUTH = (1LL << 5)     //!< The face is occluded by mouth.
		
	};

	/**
	* Face occlusion status.
	*/
	enum fv_enum_OCCLUSION_STATUS
	{
		FR_OCCLUSION_STATUS_NONE = 0,						//!< None.
		FR_OCCLUSION_STATUS_LEFT_EYE = (1LL << 0),			//!< Left Eye Occluded.
		FR_OCCLUSION_STATUS_RIGHT_EYE = (1LL << 1),			//!< Right Eye Occluded.
		FR_OCCLUSION_STATUS_NOSE = (1LL << 2),				//!< Nose Occluded.
		FR_OCCLUSION_STATUS_MOUTH = (1LL << 3),				//!< Mouth Occluded.
		FR_OCCLUSION_STATUS_MASK = (1LL << 4)				//!< Mask detected.
	};

	enum fv_QC_PREFERENCE
	{
		QC_PREFER_NONE = 0,							//!< None.
		QC_PREFER_HARDWARE_DETECTION = (1 << 1),	//!< Prefers GPU hardware acceleration on quality detection.
		QC_PREFER_FAST_DETECTION = (1 << 2),		 //!< (Deprecated) Prefers non-DNN algorithm for faster quality detection speed.
		QC_PREFER_INTEL_MOVIDIUS_VPU_DETECTION = (1 << 5) //!< Prefers Intel Movidius VPU acceleration on quality detection.
	};

	



	/**
	* The type of face feature to show.
	*/
	enum fv_FEATURE_TYPE
	{
		FEATURE_TYPE_NONE = 0,						//!< None.
		FEATURE_TYPE_STANDARD_PRECISION = 1,			//!< Standard precision.
		FEATURE_TYPE_HIGH_PRECISION = 2,				//!< High precision.
		FEATURE_TYPE_ULTRA_HIGH_PRECISION = 3,		//!< Ultra-High precision.
		FEATURE_TYPE_VERY_HIGH_PRECISION = 4,		//!< Very-High presicion.
		FEATURE_TYPE_UH3 = 5,	                    //!< 3rd generation of Ultra-High precision.
		FEATURE_TYPE_H3 = 6,							//!< 3rd generation of High precision.
		FEATURE_TYPE_UH5 = 7,	                    //!< 5th generation of Ultra-High precision.
		FEATURE_TYPE_VH5 = 8,	                    //!< 5th generation of Very-High presicion.
		FEATURE_TYPE_H5 = 9							//!< 5th generation of High precision.
	};

	
	/**
	* The sub type of face feature to show.
	*/
	enum fv_FEATURE_SUB_TYPE
	{
		FEATURE_SUB_TYPE_NONE = 0,	//!< None.
		FEATURE_SUB_TYPE_ASIAN = 1,	//!< Asian.
		FEATURE_SUB_TYPE_MASK = 2	//!< Mask.
	};

	/**
	* The type of metadata of face feature.
	*/
	enum fv_FEATURE_METADATA_TYPE
	{
		FEATURE_METADATA_TYPE_NONE = 0,	//!< None.
		FEATURE_METADATA_TYPE_MASK = 1	//!< Mask.
	};

	struct _Point
	{
		int16_t x;	//!< X.
		int16_t y;	//!< Y.
	};
	struct _Rectangle
	{
		_Point topLeft;		//!< The point of left-top corner.
		_Point bottomRight;	//!< The point of right-bottom corner.
	};

	struct _Pose
	{
		float yaw;		//!< Yaw. The angle (in degrees) for the face turning to left or right. Minus values represent angles that the face turn to his right hand side (left if see from the camera). Positive values represent angles that the face turn to his right hand side (right if see from the camera).
		float pitch;	//!< Pitch. The angle (in degrees) for the face raising up or down. Positive value means the angle that face raises up.
		float roll;		//!< Roll. The angle (in degrees) for the face roll to the left or right. Positive values means the angles that the face rolls to his right.
	};

	struct _Confidence
	{
		uint32_t size = 0;
		float confidence[100];
	};

	struct _FeatureData
	{
		uint32_t size;		//!< The size of the feature data.
		float data[2048];	//!< The feature data.
	};


	typedef int32_t fv_OCCLUSION_STATUS;
	struct	fv_FaceInfo
	{
		uint32_t sizeOfStructure;			//!< The size of the structure.
		float confidence;					//!< The confidence of the face.
		int32_t options;			//!< The options of extracted feature.
		_Rectangle boundingBox;			//!< The bounding box of the face.
		fv_OCCLUSION_STATUS occlusion;		//!< The status of face occlusion. 
	};

	struct fv_FaceAttribute
	{
		uint32_t sizeOfStructure;			//!< The size of the structure.
		int32_t options;			//!< The options of extracted feature.
		float age;							//!< The age of the face.
		int32_t emotion;					//!< The emotion of the face.
		int32_t gender;					//!< The gender of the face.
		_Pose pose;					    //!< The pose of the face.
		_Confidence emotionConfidence; //!< The emotion confidence of the face.
		_Confidence genderConfidence;  //!< The gender confidence of the face.
	};

	struct fv_FaceFeature
	{
		uint32_t sizeOfStructure;			//!< The size of the structure.
		int32_t featureType;		//!< The type of the face feature.
		int32_t featureSubType;	//!< The sub type of the face feature.
		_FeatureData featureData;			//!< The feature data of the face feature.
	};


	struct fv_FaceLandmark
	{
		uint32_t sizeOfStructure;		//!< The size of the structure.
		uint32_t featurePointSize;		//!< The size of the feature points.
		_Point featurePoints[100];	//!< The feature points. The returned array includes 5 feature points, in the order of Left Eye, Right Eye, Nose, Left point of the mouth corner, Right point of the mouth corner. See @ref FaceMeSDK::EFR_LANDMARK as the index for each landmark
	};

	struct fv_QualityDetectConfig
	{
		uint32_t sizeOfStructure;				//!< The size of the structure.
		int32_t detectType;    //!< The detect type.
		int32_t checkMode;        //!< The mode of photo quality check.
		int32_t blurDetectMode;	//!< Different detect config for blur detection
		int32_t overExposureThreshold;          //!< The threshold of over exposure.
		int32_t underExposureThreshold;         //!< The threshold of under exposure.

		uint32_t faceCount;                     //!< Count of faces. When faceCount > 0, faceInfos, faceLandmarks and poses cannot be nullptr.
		fv_FaceInfo* faceInfos;                 //!< The face information for analyzed.
		fv_FaceLandmark* faceLandmarks;         //!< The feature landmarks for analzed.
		_Pose* poses;                         //!< The face poses for analyzed.
	}; 
	
	struct fv_UserActionDetectConfig
	{
		uint32_t sizeOfStructure;				//!< The size of the structure.
		int32_t useraction;
		float confidenceThreshold;				//!< The threshold of the confidence.
		
		const fv_FaceInfo *faceInfo;			//!< The face information for analyzed.
		const fv_FaceAttribute *faceAttribute;	//!< The face attribute for analyzed.
		const fv_FaceFeature *faceFeature;		//!< The feature vector of the face to be analyzed.
		
	};



	struct fv_QualityDetectResult
	{
		uint32_t sizeOfStructure;				        //!< The size of the structure.
		int32_t issue;					//!< The detect result.
		float blur;                                     //!< The value of blurriness.
		float exposure;                                 //!< The value of exposure.
		uint32_t faceSize;                              //!< The face size. (pixel)
		_Pose wrongAngle;                             //!< The wrong face angle.
		int32_t occlusionReason;       //!< @see EFR_OCCLUSION_FAIL_REASON.
	};


}
