/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyMultipleApiHooker4.h"

onKeyMultipleApiHooker4::onKeyMultipleApiHooker4() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/TextView",
			"onKeyMultiple","(IILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyMultipleApiHooker4::~onKeyMultipleApiHooker4() {
	// TODO Auto-generated destructor stub
}

