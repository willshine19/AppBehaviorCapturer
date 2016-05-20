/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onSensorChangedApiHooker.h"

onSensorChangedApiHooker::onSensorChangedApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/OrientationListener",
			"onSensorChanged","(I[F)V",false,NULL,NULL,NULL));
}

onSensorChangedApiHooker::~onSensorChangedApiHooker() {
	// TODO Auto-generated destructor stub
}

