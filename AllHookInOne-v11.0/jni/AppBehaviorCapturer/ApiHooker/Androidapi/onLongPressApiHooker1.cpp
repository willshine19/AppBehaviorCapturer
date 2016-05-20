/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onLongPressApiHooker1.h"

onLongPressApiHooker1::onLongPressApiHooker1() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/Gallery",
			"onLongPress","(Landroid/view/MotionEvent;)V",false,NULL,NULL,NULL));
}

onLongPressApiHooker1::~onLongPressApiHooker1() {
	// TODO Auto-generated destructor stub
}

