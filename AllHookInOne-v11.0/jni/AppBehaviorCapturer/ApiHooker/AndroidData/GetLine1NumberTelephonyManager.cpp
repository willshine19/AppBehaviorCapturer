/*
 * GetLine1NumberTelephonyManager.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "GetLine1NumberTelephonyManager.h"

GetLine1NumberTelephonyManager::GetLine1NumberTelephonyManager() {
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/TelephonyManager",
			"getLine1Number","()Ljava/lang/String;",false,NULL,NULL,NULL));

}

GetLine1NumberTelephonyManager::~GetLine1NumberTelephonyManager() {
	// TODO Auto-generated destructor stub
}

bool GetLine1NumberTelephonyManager::parseResult(Object* obj) {
	StringObject* stringObjId = (StringObject*) obj;
	char* resultString = dvmCreateCstrFromString(stringObjId);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(resultString);
	return true;
}
