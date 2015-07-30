/*
 * StartMediaRecorder.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "StartMediaRecorder.h"

StartMediaRecorder::StartMediaRecorder() {
	this->mApiDeclaration = *(new ApiDeclaration("android/media/MediaRecorder",
			"start","()V", false, NULL, NULL, NULL));
}

StartMediaRecorder::~StartMediaRecorder() {
	// TODO Auto-generated destructor stub
}

