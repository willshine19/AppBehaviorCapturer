/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "CallTelephonnyApiHooker.h"

CallTelephonnyApiHooker::CallTelephonnyApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("com/android/internal/telephony/ITelephony$Stub$Proxy",
			"call","(Ljava/lang/String;)V",false,NULL,NULL,NULL));
}

CallTelephonnyApiHooker::~CallTelephonnyApiHooker() {
	// TODO Auto-generated destructor stub
}

