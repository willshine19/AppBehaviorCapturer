/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "ServiceApiHooker.h"

ServiceApiHooker::ServiceApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Service",
			"<init>","()V",false,NULL,NULL,NULL));
}

ServiceApiHooker::~ServiceApiHooker() {
	// TODO Auto-generated destructor stub
}

