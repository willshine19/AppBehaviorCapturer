/*
 * RequestLocationUpdatesLocationManager.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "RequestLocationUpdatesLocationManager.h"

RequestLocationUpdatesLocationManager::RequestLocationUpdatesLocationManager() {
	this->mApiDeclaration = *(new ApiDeclaration("android/location/LocationManager",
			"requestLocationUpdates","(JFLandroid/location/Criteria;Landroid/app/PendingIntent;)V",false,NULL,NULL,NULL));


}

RequestLocationUpdatesLocationManager::~RequestLocationUpdatesLocationManager() {
	// TODO Auto-generated destructor stub
}

