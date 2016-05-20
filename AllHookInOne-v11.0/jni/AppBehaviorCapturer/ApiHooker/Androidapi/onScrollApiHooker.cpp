/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onScrollApiHooker.h"

onScrollApiHooker::onScrollApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/GestureDetector$SimpleOnGestureListener",
			"onScroll","(Landroid/view/MotionEvent;Landroid/view/MotionEvent;FF)Z",false,NULL,NULL,NULL));
}

onScrollApiHooker::~onScrollApiHooker() {
	// TODO Auto-generated destructor stub
}

