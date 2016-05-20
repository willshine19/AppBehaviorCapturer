/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getLine1NumberApiHooker.h"

getLine1NumberApiHooker::getLine1NumberApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/TelephonyManager",
			"getLine1Number","()Ljava/lang/String;",false,NULL,NULL,NULL));
}

getLine1NumberApiHooker::~getLine1NumberApiHooker() {
	// TODO Auto-generated destructor stub
}

