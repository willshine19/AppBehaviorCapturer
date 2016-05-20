/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onTouchEvent1ApiHooker.h"

onTouchEvent1ApiHooker::onTouchEvent1ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/GestureDetector",
			"onTouchEvent1","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onTouchEvent1ApiHooker::~onTouchEvent1ApiHooker() {
	// TODO Auto-generated destructor stub
}

