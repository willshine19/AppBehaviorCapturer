/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onTouchEventApiHooker4.h"

onTouchEventApiHooker4::onTouchEventApiHooker4() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/HorizontalScrollView",
			"onTouchEvent","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onTouchEventApiHooker4::~onTouchEventApiHooker4() {
	// TODO Auto-generated destructor stub
}

