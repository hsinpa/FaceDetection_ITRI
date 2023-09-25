#pragma once

#include "base_def.h"
#include <stdio.h>
#include <string>
#include <strsafe.h>

#include <memory>




	class UserFaceItem
	{
	public:
		UserFaceItem()
		{
			std::memset(&faceInfo, 0, sizeof(FV_ADV::fv_FaceInfo));
			faceInfo.sizeOfStructure = sizeof(FV_ADV::fv_FaceInfo);

			std::memset(&faceAttribute, 0, sizeof(FV_ADV::fv_FaceAttribute));
			faceAttribute.sizeOfStructure = sizeof(FV_ADV::fv_FaceAttribute);

			std::memset(&faceFeature, 0, sizeof(FV_ADV::fv_FaceFeature));
			faceFeature.sizeOfStructure = sizeof(FV_ADV::fv_FaceFeature);

			std::memset(&face_landmark, 0, sizeof(FV_ADV::fv_FaceLandmark));
			face_landmark.sizeOfStructure = sizeof(FV_ADV::fv_FaceLandmark);

			mask_state = FV_ADV::fv_mask_state::fv_mask_disappear;
			
		};

		FV_ADV::fv_FaceInfo faceInfo;
		FV_ADV::fv_FaceAttribute faceAttribute;
		FV_ADV::fv_FaceFeature faceFeature;
		FV_ADV::fv_FaceLandmark face_landmark;
		uint32_t mask_state; // 2: wear mask well, 1: wear mask incorrectly , 0: not wearing mask 
		std::string name;

	};

