/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onTouchEventApiHooker2.h"

onTouchEventApiHooker2::onTouchEventApiHooker2() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/TouchDelegate",
			"onTouchEvent","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onTouchEventApiHooker2::~onTouchEventApiHooker2() {
	// TODO Auto-generated destructor stub
}

