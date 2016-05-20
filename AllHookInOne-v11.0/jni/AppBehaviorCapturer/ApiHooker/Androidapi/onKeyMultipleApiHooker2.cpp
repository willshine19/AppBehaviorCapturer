/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyMultipleApiHooker2.h"

onKeyMultipleApiHooker2::onKeyMultipleApiHooker2() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/GridView",
			"onKeyMultiple","(IILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyMultipleApiHooker2::~onKeyMultipleApiHooker2() {
	// TODO Auto-generated destructor stub
}

