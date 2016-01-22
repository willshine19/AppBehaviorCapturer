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

bool DisconnectWifiManager::parseResult(Object* obj) {
	const char* className = "java/lang/Boolean";
	char* resultString = parseObjectToString(obj, className);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(resultString);
	return true;
}
