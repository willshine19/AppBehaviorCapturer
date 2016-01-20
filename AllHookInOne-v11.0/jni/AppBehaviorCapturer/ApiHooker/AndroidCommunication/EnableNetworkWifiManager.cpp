/*
 * EnableNetworkWifiManager.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "EnableNetworkWifiManager.h"

EnableNetworkWifiManager::EnableNetworkWifiManager() {
	this->mApiDeclaration = *(new ApiDeclaration("android/net/wifi/WifiManager",
				"enableNetwork","(IZ)Z",false,NULL,NULL,NULL));

}

EnableNetworkWifiManager::~EnableNetworkWifiManager() {
	// TODO Auto-generated destructor stub
}

bool EnableNetworkWifiManager::parseResult(Object* obj) {
	const char* className = "java/lang/Boolean";
	char* resultString = parseObjectToString(obj, className);
	LOGD("[返回值解析] -> %s", resultString);
	return true;
}

