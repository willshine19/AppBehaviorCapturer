/*
 * SetWifiEnabledWifiManager.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "SetWifiEnabledWifiManager.h"

SetWifiEnabledWifiManager::SetWifiEnabledWifiManager() {
	this->mApiDeclaration = *(new ApiDeclaration("android/net/wifi/WifiManager",
				"setWifiEnabled","(Z)Z",false,NULL,NULL,NULL));

}

SetWifiEnabledWifiManager::~SetWifiEnabledWifiManager() {
	// TODO Auto-generated destructor stub
}

