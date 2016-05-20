/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onDoubleTapEventApiHooker.h"

onDoubleTapEventApiHooker::onDoubleTapEventApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/GestureDetector$SimpleOnGestureListener",
			"onDoubleTapEvent","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onDoubleTapEventApiHooker::~onDoubleTapEventApiHooker() {
	// TODO Auto-generated destructor stub
}

