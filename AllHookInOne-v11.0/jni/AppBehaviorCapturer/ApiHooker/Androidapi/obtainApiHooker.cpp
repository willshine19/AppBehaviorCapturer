/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "obtainApiHooker.h"

obtainApiHooker::obtainApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/os/Message",
			"<init>","()V",false,NULL,NULL,NULL));
}

obtainApiHooker::~obtainApiHooker() {
	// TODO Auto-generated destructor stub
}

