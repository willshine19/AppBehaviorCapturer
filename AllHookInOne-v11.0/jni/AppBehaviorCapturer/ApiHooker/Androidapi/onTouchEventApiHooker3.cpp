/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onTouchEventApiHooker3.h"

onTouchEventApiHooker3::onTouchEventApiHooker3() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/AbsListView",
			"onTouchEvent","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onTouchEventApiHooker3::~onTouchEventApiHooker3() {
	// TODO Auto-generated destructor stub
}

