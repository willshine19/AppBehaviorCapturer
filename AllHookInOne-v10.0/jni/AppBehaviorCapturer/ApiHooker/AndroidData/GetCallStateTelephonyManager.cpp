/*
 * GetCallStateTelephonyManager.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "GetCallStateTelephonyManager.h"

GetCallStateTelephonyManager::GetCallStateTelephonyManager() {
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/TelephonyManager",
			"getCallState","()I",false,NULL,NULL,NULL));

}

GetCallStateTelephonyManager::~GetCallStateTelephonyManager() {
	// TODO Auto-generated destructor stub
}

