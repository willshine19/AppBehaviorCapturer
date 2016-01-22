/*
 * AddGpsStatusListenerLocationManager.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "AddGpsStatusListenerLocationManager.h"

AddGpsStatusListenerLocationManager::AddGpsStatusListenerLocationManager() {
	//modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/location/LocationManager",
			"addGpsStatusListener","(Landroid/location/GpsStatus$Listener;)Z",false,NULL,NULL,NULL));
}

AddGpsStatusListenerLocationManager::~AddGpsStatusListenerLocationManager() {
	// TODO Auto-generated destructor stub
}

bool AddGpsStatusListenerLocationManager::parseResult(Object* obj) {
	const char* className = "java/lang/Boolean";
	char* resultString = parseObjectToString(obj, className);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(resultString);
	return true;
}
