/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyDownApiHooker2.h"

onKeyDownApiHooker2::onKeyDownApiHooker2() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/TextView",
			"onKeyDown","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyDownApiHooker2::~onKeyDownApiHooker2() {
	// TODO Auto-generated destructor stub
}

