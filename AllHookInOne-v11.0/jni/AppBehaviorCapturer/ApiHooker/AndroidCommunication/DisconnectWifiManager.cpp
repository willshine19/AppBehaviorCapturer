/*
 * DisconnectWifiManager.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "DisconnectWifiManager.h"

DisconnectWifiManager::DisconnectWifiManager() {
	this->mApiDeclaration = *(new ApiDeclaration("android/net/wifi/WifiManager",
				"disconnect","()Z",false,NULL,NULL,NULL));

}

DisconnectWifiManager::~DisconnectWifiManager() {
	// TODO Auto-generated destructor stub
}

