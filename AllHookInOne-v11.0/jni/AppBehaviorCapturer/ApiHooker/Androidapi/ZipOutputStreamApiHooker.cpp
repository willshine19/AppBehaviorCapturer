/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "ZipOutputStreamApiHooker.h"

ZipOutputStreamApiHooker::ZipOutputStreamApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/util/zip",
			"ZipOutputStream","(Ljava/io/OutputStream;)",false,NULL,NULL,NULL));
}

ZipOutputStreamApiHooker::~ZipOutputStreamApiHooker() {
	// TODO Auto-generated destructor stub
}

