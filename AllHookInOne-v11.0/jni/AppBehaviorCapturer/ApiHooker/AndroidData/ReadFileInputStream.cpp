/*
 * ReadFileInputStream.cpp
 *
 *  Created on: 2015-6-18
 *      Author: sang
 */

#include "ReadFileInputStream.h"

ReadFileInputStream::ReadFileInputStream() {
	this->mApiDeclaration = *(new ApiDeclaration("java/io/FileInputStream",
			"read","([BII)I",false,NULL,NULL,NULL));

}

ReadFileInputStream::~ReadFileInputStream() {
	// TODO Auto-generated destructor stub
}

bool ReadFileInputStream::parseResult(Object* obj) {
	char rs[20];
	int* ma ;
	int i = 0;
	ma = (int*) obj;
	i = reinterpret_cast<int>(&ma[0]);
	sprintf(rs, "%d", i);
	LOGD("[返回值解析] -> %s", rs);
	return true;
}
