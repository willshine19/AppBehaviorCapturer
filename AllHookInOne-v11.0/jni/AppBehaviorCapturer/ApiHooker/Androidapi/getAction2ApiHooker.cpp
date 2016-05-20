/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getAction2ApiHooker.h"

getAction2ApiHooker::getAction2ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/MotionEvent",
			"getAction","()I",false,NULL,NULL,NULL));
}

getAction2ApiHooker::~getAction2ApiHooker() {
	// TODO Auto-generated destructor stub
}

