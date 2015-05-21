/*
 * GetMacAddressWifiInfoApiHooker.cpp
 *
 *  Created on: 2015-5-13
 *      Author: long
 */

#include "GetMacAddressWifiInfoApiHooker.h"


GetMacAddressWifiInfoApiHooker::GetMacAddressWifiInfoApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/net/wifi/WifiInfo",
			"getMacAddress","()Ljava/lang/String;",false,NULL,NULL,NULL));
	this->mCollectedApiInfo = *(new CollectedApiInfo());
}

GetMacAddressWifiInfoApiHooker::~GetMacAddressWifiInfoApiHooker() {
	// TODO Auto-generated destructor stub
}
