/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onTouchEventApiHooker6.h"

onTouchEventApiHooker6::onTouchEventApiHooker6() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/Gallery",
			"onTouchEvent","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onTouchEventApiHooker6::~onTouchEventApiHooker6() {
	// TODO Auto-generated destructor stub
}

