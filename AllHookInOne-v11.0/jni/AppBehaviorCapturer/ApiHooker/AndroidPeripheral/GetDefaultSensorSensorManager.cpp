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

bool GetDefaultSensorSensorManager::parseResult(Object* obj) {
	const char* className = "android/hardware/Sensor";
	char* resultString = parseObjectToString(obj, className);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(resultString);
	return true;
}
