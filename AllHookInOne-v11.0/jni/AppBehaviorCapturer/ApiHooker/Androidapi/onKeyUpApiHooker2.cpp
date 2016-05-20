/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyUpApiHooker2.h"

onKeyUpApiHooker2::onKeyUpApiHooker2() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/TextView",
			"onKeyUp","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyUpApiHooker2::~onKeyUpApiHooker2() {
	// TODO Auto-generated destructor stub
}

