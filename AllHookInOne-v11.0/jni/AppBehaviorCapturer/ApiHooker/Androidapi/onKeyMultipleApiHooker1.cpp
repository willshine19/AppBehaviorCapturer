/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyMultipleApiHooker1.h"

onKeyMultipleApiHooker1::onKeyMultipleApiHooker1() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Dialog",
			"onKeyMultiple","(IILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyMultipleApiHooker1::~onKeyMultipleApiHooker1() {
	// TODO Auto-generated destructor stub
}

