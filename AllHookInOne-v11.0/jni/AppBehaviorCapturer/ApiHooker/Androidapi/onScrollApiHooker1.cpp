/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onScrollApiHooker1.h"

onScrollApiHooker1::onScrollApiHooker1() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/Gallery",
			"onScroll","(Landroid/view/MotionEvent;Landroid/view/MotionEvent;FF)Z",false,NULL,NULL,NULL));
}

onScrollApiHooker1::~onScrollApiHooker1() {
	// TODO Auto-generated destructor stub
}

