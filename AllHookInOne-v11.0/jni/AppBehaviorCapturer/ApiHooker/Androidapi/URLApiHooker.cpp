/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "URLApiHooker.h"

URLApiHooker::URLApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/net/URL",
			"<init>","(Ljava/lang/String;)V",false,NULL,NULL,NULL));
}

URLApiHooker::~URLApiHooker() {
	// TODO Auto-generated destructor stub
}

