/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onSingleTapConfirmedApiHooker.h"

onSingleTapConfirmedApiHooker::onSingleTapConfirmedApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/GestureDetector$SimpleOnGestureListener",
			"onSingleTapConfirmed","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onSingleTapConfirmedApiHooker::~onSingleTapConfirmedApiHooker() {
	// TODO Auto-generated destructor stub
}

