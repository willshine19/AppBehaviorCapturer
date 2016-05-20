/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onLongPressApiHooker.h"

onLongPressApiHooker::onLongPressApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/GestureDetector$SimpleOnGestureListener",
			"onLongPress","(Landroid/view/MotionEvent;)V",false,NULL,NULL,NULL));
}

onLongPressApiHooker::~onLongPressApiHooker() {
	// TODO Auto-generated destructor stub
}

