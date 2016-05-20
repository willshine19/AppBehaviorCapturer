/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getActionApiHooker.h"

getActionApiHooker::getActionApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/KeyEvent",
			"getAction","()I",false,NULL,NULL,NULL));
}

getActionApiHooker::~getActionApiHooker() {
	// TODO Auto-generated destructor stub
}

