/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onTouchEventApiHooker9.h"

onTouchEventApiHooker9::onTouchEventApiHooker9() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"onTouchEvent","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onTouchEventApiHooker9::~onTouchEventApiHooker9() {
	// TODO Auto-generated destructor stub
}

