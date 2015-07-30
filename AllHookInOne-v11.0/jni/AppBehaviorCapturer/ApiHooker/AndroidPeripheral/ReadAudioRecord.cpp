/*
 * ReadAudioRecord.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "ReadAudioRecord.h"

ReadAudioRecord::ReadAudioRecord() {
	this->mApiDeclaration = *(new ApiDeclaration("android/media/AudioRecord",
			"read","(Ljava/nio/ByteBuffer;I)I", false, NULL, NULL, NULL));

}

ReadAudioRecord::~ReadAudioRecord() {
	// TODO Auto-generated destructor stub
}

