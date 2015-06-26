/*
 * PrepareMediaRecorder.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "PrepareMediaRecorder.h"

PrepareMediaRecorder::PrepareMediaRecorder() {
	this->mApiDeclaration = *(new ApiDeclaration("android/media/MediaRecorder",
			"prepare","()V", false, NULL, NULL, NULL));
}

PrepareMediaRecorder::~PrepareMediaRecorder() {
	// TODO Auto-generated destructor stub
}

