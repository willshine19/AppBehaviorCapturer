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

