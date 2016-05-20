/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onTouchEventApiHooker7.h"

onTouchEventApiHooker7::onTouchEventApiHooker7() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/Spinner",
			"onTouchEvent","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onTouchEventApiHooker7::~onTouchEventApiHooker7() {
	// TODO Auto-generated destructor stub
}

