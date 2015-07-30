/*
 * GetDefaultSensorSensorManager.cpp
 *
 *  Created on: 2015-6-17
 *      Author: sang
 */

#include "GetDefaultSensorSensorManager.h"

GetDefaultSensorSensorManager::GetDefaultSensorSensorManager() {
	this->mApiDeclaration = *(new ApiDeclaration("android/hardware/SensorManager",
			"getDefaultSensor","(I)Landroid/hardware/Sensor;",false,NULL,NULL,NULL));

}

GetDefaultSensorSensorManager::~GetDefaultSensorSensorManager() {
	// TODO Auto-generated destructor stub
}

