/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onDownApiHooker1.h"

onDownApiHooker1::onDownApiHooker1() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/Gallery",
			"onDown","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onDownApiHooker1::~onDownApiHooker1() {
	// TODO Auto-generated destructor stub
}

