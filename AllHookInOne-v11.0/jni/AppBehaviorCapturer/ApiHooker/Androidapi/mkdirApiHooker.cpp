/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "mkdirApiHooker.h"

mkdirApiHooker::mkdirApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/io/File",
			"mkdir","()Z",false,NULL,NULL,NULL));
}

mkdirApiHooker::~mkdirApiHooker() {
	// TODO Auto-generated destructor stub
}

