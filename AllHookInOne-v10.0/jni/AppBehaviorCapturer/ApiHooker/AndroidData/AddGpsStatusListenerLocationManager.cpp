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

