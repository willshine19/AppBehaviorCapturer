/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "vApiHooker.h"

vApiHooker::vApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/util/Log",
			"v","(Ljava/lang/String;Ljava/lang/String;)I",true,NULL,NULL,NULL));
}

vApiHooker::~vApiHooker() {
	// TODO Auto-generated destructor stub
}

