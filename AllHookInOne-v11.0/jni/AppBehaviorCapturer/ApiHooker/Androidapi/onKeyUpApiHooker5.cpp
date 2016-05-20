/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyUpApiHooker5.h"

onKeyUpApiHooker5::onKeyUpApiHooker5() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/ListPopupWindow",
			"onKeyUp","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyUpApiHooker5::~onKeyUpApiHooker5() {
	// TODO Auto-generated destructor stub
}

