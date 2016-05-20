/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onShowPressApiHooker1.h"

onShowPressApiHooker1::onShowPressApiHooker1() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/GestureDetector$SimpleOnGestureListener",
			"onShowPress","(Landroid/view/MotionEvent;)V",false,NULL,NULL,NULL));
}

onShowPressApiHooker1::~onShowPressApiHooker1() {
	// TODO Auto-generated destructor stub
}

