/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "openApiHooker.h"

openApiHooker::openApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/hardware/Camera",
			"open","(I)Landroid/hardware/Camera;",true,NULL,NULL,NULL));
}

openApiHooker::~openApiHooker() {
	// TODO Auto-generated destructor stub
}

