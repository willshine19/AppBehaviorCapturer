/*
 * GetSimSerialNumberTelephonyManager.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "GetSimSerialNumberTelephonyManager.h"

GetSimSerialNumberTelephonyManager::GetSimSerialNumberTelephonyManager() {
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/TelephonyManager",
			"getSimSerialNumber","()Ljava/lang/String;",false,NULL,NULL,NULL));

}

GetSimSerialNumberTelephonyManager::~GetSimSerialNumberTelephonyManager() {
	// TODO Auto-generated destructor stub
}

