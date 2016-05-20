/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onDownApiHooker.h"

onDownApiHooker::onDownApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/GestureDetector$SimpleOnGestureListener",
			"onDown","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onDownApiHooker::~onDownApiHooker() {
	// TODO Auto-generated destructor stub
}

