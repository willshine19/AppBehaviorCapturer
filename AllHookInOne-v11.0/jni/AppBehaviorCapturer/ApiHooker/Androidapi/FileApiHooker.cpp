/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "FileApiHooker.h"

FileApiHooker::FileApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/io/File",
			"<init>","(Ljava/lang/String;)V",false,NULL,NULL,NULL));
}

FileApiHooker::~FileApiHooker() {
	// TODO Auto-generated destructor stub
}

