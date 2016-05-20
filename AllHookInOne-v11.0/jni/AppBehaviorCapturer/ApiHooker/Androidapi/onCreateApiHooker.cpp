/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onCreateApiHooker.h"

onCreateApiHooker::onCreateApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"onCreate","(Landroid/os/Bundle;)V",false,NULL,NULL,NULL));
}

onCreateApiHooker::~onCreateApiHooker() {
	// TODO Auto-generated destructor stub
}

