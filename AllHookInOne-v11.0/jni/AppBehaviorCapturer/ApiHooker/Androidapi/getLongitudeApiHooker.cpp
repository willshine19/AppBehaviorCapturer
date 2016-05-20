/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getLongitudeApiHooker.h"

getLongitudeApiHooker::getLongitudeApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/location/Location",
			"getLongitude","()D",false,NULL,NULL,NULL));
}

getLongitudeApiHooker::~getLongitudeApiHooker() {
	// TODO Auto-generated destructor stub
}

