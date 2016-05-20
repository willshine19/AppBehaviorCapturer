/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getDeviceIdApiHooker.h"

getDeviceIdApiHooker::getDeviceIdApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/TelephonyManager",
			"getDeviceId","()Ljava/lang/String;",false,NULL,NULL,NULL));
}

getDeviceIdApiHooker::~getDeviceIdApiHooker() {
	// TODO Auto-generated destructor stub
}

