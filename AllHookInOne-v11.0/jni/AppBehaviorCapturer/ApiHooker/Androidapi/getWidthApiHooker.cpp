/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getWidthApiHooker.h"

getWidthApiHooker::getWidthApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/Display",
			"getWidth","()I",false,NULL,NULL,NULL));
}

getWidthApiHooker::~getWidthApiHooker() {
	// TODO Auto-generated destructor stub
}

