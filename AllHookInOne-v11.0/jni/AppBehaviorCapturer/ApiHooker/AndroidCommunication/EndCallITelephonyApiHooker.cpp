/*
 * EndCallITelephonyApiHooker.cpp
 *
 *  Created on: 2015-6-25
 *      Author: long
 */

#include "EndCallITelephonyApiHooker.h"

EndCallITelephonyApiHooker::EndCallITelephonyApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("com/android/internal/telephony/ITelephony$Stub$Proxy",
			"endCall","()Z",false,NULL,NULL,NULL));
}

EndCallITelephonyApiHooker::~EndCallITelephonyApiHooker() {
	// TODO Auto-generated destructor stub
}

