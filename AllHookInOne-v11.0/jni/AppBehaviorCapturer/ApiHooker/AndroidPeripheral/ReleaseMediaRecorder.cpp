/*
 * ReleaseMediaRecorder.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "ReleaseMediaRecorder.h"

ReleaseMediaRecorder::ReleaseMediaRecorder() {
	this->mApiDeclaration = *(new ApiDeclaration("android/media/MediaRecorder",
			"release","()V", false, NULL, NULL, NULL));
}

ReleaseMediaRecorder::~ReleaseMediaRecorder() {
	// TODO Auto-generated destructor stub
}

