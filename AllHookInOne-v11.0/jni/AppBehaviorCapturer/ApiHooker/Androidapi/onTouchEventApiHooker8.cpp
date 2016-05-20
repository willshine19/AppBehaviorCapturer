/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onTouchEventApiHooker8.h"

onTouchEventApiHooker8::onTouchEventApiHooker8() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/TextView",
			"onTouchEvent","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onTouchEventApiHooker8::~onTouchEventApiHooker8() {
	// TODO Auto-generated destructor stub
}

