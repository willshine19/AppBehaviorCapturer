/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "FileOutputStreamApiHooker.h"

FileOutputStreamApiHooker::FileOutputStreamApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/io/FileOutputStream",
			"<init>","(Ljava/io/File;)V",false,NULL,NULL,NULL));
}

FileOutputStreamApiHooker::~FileOutputStreamApiHooker() {
	// TODO Auto-generated destructor stub
}

