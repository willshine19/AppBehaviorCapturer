/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onFlingApiHooker.h"

onFlingApiHooker::onFlingApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/GestureDetector$SimpleOnGestureListener",
			"onFling","(Landroid/view/MotionEvent;Landroid/view/MotionEvent;FF)Z",false,NULL,NULL,NULL));
}

onFlingApiHooker::~onFlingApiHooker() {
	// TODO Auto-generated destructor stub
}

