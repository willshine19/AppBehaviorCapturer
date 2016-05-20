/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onFlingApiHooker1.h"

onFlingApiHooker1::onFlingApiHooker1() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/Gallery",
			"onFling","(Landroid/view/MotionEvent;Landroid/view/MotionEvent;FF)Z",false,NULL,NULL,NULL));
}

onFlingApiHooker1::~onFlingApiHooker1() {
	// TODO Auto-generated destructor stub
}

