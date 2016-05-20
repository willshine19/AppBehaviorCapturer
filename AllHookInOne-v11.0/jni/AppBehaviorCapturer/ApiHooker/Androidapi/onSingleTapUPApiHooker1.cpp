/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onSingleTapUPApiHooker1.h"

onSingleTapUPApiHooker1::onSingleTapUPApiHooker1() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/Gallery",
			"onSingleTapUp","(Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

onSingleTapUPApiHooker1::~onSingleTapUPApiHooker1() {
	// TODO Auto-generated destructor stub
}

