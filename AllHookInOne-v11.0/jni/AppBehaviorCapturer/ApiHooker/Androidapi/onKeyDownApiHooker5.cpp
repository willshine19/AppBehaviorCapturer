/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyDownApiHooker5.h"

onKeyDownApiHooker5::onKeyDownApiHooker5() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/ListPopupWindow",
			"onKeyDown","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyDownApiHooker5::~onKeyDownApiHooker5() {
	// TODO Auto-generated destructor stub
}

