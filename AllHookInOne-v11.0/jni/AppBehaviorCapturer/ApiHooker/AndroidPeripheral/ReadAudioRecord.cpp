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

bool ReadAudioRecord::parseResult(Object* obj) {
	char rs[20];
	int* ma ;
	int i = 0;
	ma = (int*) obj;
	i = reinterpret_cast<int>(&ma[0]);
	sprintf(rs, "%d", i);
	LOGD("[返回值解析] -> %s", rs);
	return true;
}
