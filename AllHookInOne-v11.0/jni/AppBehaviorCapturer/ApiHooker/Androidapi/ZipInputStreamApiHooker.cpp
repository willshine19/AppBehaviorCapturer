/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "ZipInputStreamApiHooker.h"

ZipInputStreamApiHooker::ZipInputStreamApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/util/zip",
			"ZipInputStream","(Ljava/io/InputStream;)",false,NULL,NULL,NULL));
}

ZipInputStreamApiHooker::~ZipInputStreamApiHooker() {
	// TODO Auto-generated destructor stub
}

