/*
 * GetFDFileInputStream.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "GetFDFileInputStream.h"

GetFDFileInputStream::GetFDFileInputStream() {
	this->mApiDeclaration = *(new ApiDeclaration("java/io/FileInputStream",
			"getFD", "()Ljava/io/FileDescriptor;", false, NULL, NULL, NULL));

}

GetFDFileInputStream::~GetFDFileInputStream() {
	// TODO Auto-generated destructor stub
}

bool GetFDFileInputStream::parseResult(Object* obj) {
	const char* className = "java/io/FileDescriptor";
	char* resultString = parseObjectToString(obj, className);
	LOGD("[返回值解析] -> %s", resultString);
	return true;
}

