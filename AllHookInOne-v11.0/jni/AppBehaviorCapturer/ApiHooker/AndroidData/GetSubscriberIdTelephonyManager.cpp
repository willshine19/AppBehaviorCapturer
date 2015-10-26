/*
 * GetSubscriberIdTelephonyManager.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "GetSubscriberIdTelephonyManager.h"

GetSubscriberIdTelephonyManager::GetSubscriberIdTelephonyManager() {
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/TelephonyManager",
			"getSubscriberId","()Ljava/lang/String;",false,NULL,NULL,NULL));

}

GetSubscriberIdTelephonyManager::~GetSubscriberIdTelephonyManager() {
	// TODO Auto-generated destructor stub
}

