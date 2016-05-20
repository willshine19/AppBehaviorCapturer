/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onTouchEventApiHooker5.h"

onTouchEventApiHooker5::onTouchEventApiHooker5() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/webkit/WebView",
			"onTouchEvent","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onTouchEventApiHooker5::~onTouchEventApiHooker5() {
	// TODO Auto-generated destructor stub
}

