/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "FileInputStreamApiHooker.h"

FileInputStreamApiHooker::FileInputStreamApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/io/FileInputStream",
			"<init>","(Ljava/io/File;)V",false,NULL,NULL,NULL));
}

FileInputStreamApiHooker::~FileInputStreamApiHooker() {
	// TODO Auto-generated destructor stub
}

