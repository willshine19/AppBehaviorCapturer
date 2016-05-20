/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onAccuracyChangedApiHooker.h"

onAccuracyChangedApiHooker::onAccuracyChangedApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/OrientationListener",
			"onAccuracyChanged","(II)V",false,NULL,NULL,NULL));
}

onAccuracyChangedApiHooker::~onAccuracyChangedApiHooker() {
	// TODO Auto-generated destructor stub
}

