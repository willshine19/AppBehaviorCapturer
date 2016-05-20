/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onSingleTapUPApiHooker.h"

onSingleTapUPApiHooker::onSingleTapUPApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/GestureDetector$SimpleOnGestureListener",
			"onSingleTapUp","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onSingleTapUPApiHooker::~onSingleTapUPApiHooker() {
	// TODO Auto-generated destructor stub
}

