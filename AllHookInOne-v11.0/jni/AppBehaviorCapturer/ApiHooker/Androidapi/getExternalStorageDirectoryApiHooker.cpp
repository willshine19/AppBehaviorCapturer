/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getExternalStorageDirectoryApiHooker.h"

getExternalStorageDirectoryApiHooker::getExternalStorageDirectoryApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/os/Environment",
			"getExternalStorageDirectory","()Ljava/io/File;",true,NULL,NULL,NULL));
}

getExternalStorageDirectoryApiHooker::~getExternalStorageDirectoryApiHooker() {
	// TODO Auto-generated destructor stub
}

