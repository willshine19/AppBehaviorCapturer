/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyMultipleApiHooker3.h"

onKeyMultipleApiHooker3::onKeyMultipleApiHooker3() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/ListView",
			"onKeyMultiple","(IILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyMultipleApiHooker3::~onKeyMultipleApiHooker3() {
	// TODO Auto-generated destructor stub
}

