/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "setPackageApiHooker.h"

setPackageApiHooker::setPackageApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/content/Intent",
			"setPackage","(Ljava/lang/String;)Landroid/content/Intent;",false,NULL,NULL,NULL));
}

setPackageApiHooker::~setPackageApiHooker() {
	// TODO Auto-generated destructor stub
}

