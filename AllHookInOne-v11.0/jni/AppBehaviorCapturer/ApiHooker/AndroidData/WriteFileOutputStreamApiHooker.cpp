/*
 * writeFileOutputStreamApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "WriteFileOutputStreamApiHooker.h"

WriteFileOutputStreamApiHooker::WriteFileOutputStreamApiHooker() {
	// TODO Auto-generated constructor stub
	this->mApiDeclaration = *(new ApiDeclaration("java/io/FileOutputStream",
				"write","(I)V",false,NULL,NULL,NULL));
}

WriteFileOutputStreamApiHooker::~WriteFileOutputStreamApiHooker() {
	// TODO Auto-generated destructor stub
}
bool WriteFileOutputStreamApiHooker::parseParameter(const u4* args){
	int temp = args[1];
	LOGD("WriteFileOutputStream's parameter is %d",temp);
	return true;
}
