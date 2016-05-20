/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyMultipleApiHooker5.h"

onKeyMultipleApiHooker5::onKeyMultipleApiHooker5() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"onKeyMultiple","(IILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyMultipleApiHooker5::~onKeyMultipleApiHooker5() {
	// TODO Auto-generated destructor stub
}

