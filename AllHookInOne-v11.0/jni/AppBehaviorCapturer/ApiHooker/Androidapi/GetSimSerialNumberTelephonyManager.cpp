/*
 * GetSimSerialNumberTelephonyManager.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "GetSimSerialNumberTelephonyManager.h"

GetSimSerialNumberTelephonyManager::GetSimSerialNumberTelephonyManager() {
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/TelephonyManager",
			"getSimSerialNumber","()Ljava/lang/String;",false,NULL,NULL,NULL));

}

GetSimSerialNumberTelephonyManager::~GetSimSerialNumberTelephonyManager() {
	// TODO Auto-generated destructor stub
}

bool GetSimSerialNumberTelephonyManager::parseResult(Object* obj) {
	StringObject* stringObjId = (StringObject*) obj;
	char* resultString = dvmCreateCstrFromString(stringObjId);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(resultString);
	return true;
}
