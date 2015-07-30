/*
 * StartRecordingAudioRecord.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "StartRecordingAudioRecord.h"

StartRecordingAudioRecord::StartRecordingAudioRecord() {
	this->mApiDeclaration = *(new ApiDeclaration("android/media/AudioRecord",
			"startRecording","()V", false, NULL, NULL, NULL));
}

StartRecordingAudioRecord::~StartRecordingAudioRecord() {
	// TODO Auto-generated destructor stub
}

