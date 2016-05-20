/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "startActivityApiHooker.h"

startActivityApiHooker::startActivityApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"startActivity","(Landroid/content/Intent;)V",false,NULL,NULL,NULL));
}

startActivityApiHooker::~startActivityApiHooker() {
	// TODO Auto-generated destructor stub
}

