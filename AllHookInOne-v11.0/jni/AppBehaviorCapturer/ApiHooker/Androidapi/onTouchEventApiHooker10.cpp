/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onTouchEventApiHooker10.h"

onTouchEventApiHooker10::onTouchEventApiHooker10() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Dialog",
			"onTouchEvent","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onTouchEventApiHooker10::~onTouchEventApiHooker10() {
	// TODO Auto-generated destructor stub
}

