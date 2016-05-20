/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onShowPressApiHooker.h"

onShowPressApiHooker::onShowPressApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/Gallery",
			"onShowPress","(Landroid/view/MotionEvent;)V",false,NULL,NULL,NULL));
}

onShowPressApiHooker::~onShowPressApiHooker() {
	// TODO Auto-generated destructor stub
}

