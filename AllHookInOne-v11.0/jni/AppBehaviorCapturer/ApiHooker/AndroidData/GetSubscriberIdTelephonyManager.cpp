/*
 * GetSubscriberIdTelephonyManager.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "GetSubscriberIdTelephonyManager.h"

GetSubscriberIdTelephonyManager::GetSubscriberIdTelephonyManager() {
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/TelephonyManager",
			"getSubscriberId","()Ljava/lang/String;",false,NULL,NULL,NULL));

}

GetSubscriberIdTelephonyManager::~GetSubscriberIdTelephonyManager() {
	// TODO Auto-generated destructor stub
}

bool GetSubscriberIdTelephonyManager::parseResult(Object* obj) {
	StringObject* stringObjId = (StringObject*) obj;
	char* resultString = dvmCreateCstrFromString(stringObjId);
//	LOGD("[返回值解析] Object-> %s", obj);
//	LOGD("[返回值解析] stringObjId-> %s", stringObjId);
	LOGD("[返回值解析] -> %s", resultString);
//	string m(resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(resultString);
	return true;
}
