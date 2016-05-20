/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyDownApiHooker10.h"

onKeyDownApiHooker10::onKeyDownApiHooker10() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/support/v7/widget/SearchView",
			"onKeyDown","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyDownApiHooker10::~onKeyDownApiHooker10() {
	// TODO Auto-generated destructor stub
}

