/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "LinkMovementMethodApiHooker.h"

LinkMovementMethodApiHooker::LinkMovementMethodApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/text/method/LinkMovementMethod",
			"<init>","()V",false,NULL,NULL,NULL));
}

LinkMovementMethodApiHooker::~LinkMovementMethodApiHooker() {
	// TODO Auto-generated destructor stub
}

