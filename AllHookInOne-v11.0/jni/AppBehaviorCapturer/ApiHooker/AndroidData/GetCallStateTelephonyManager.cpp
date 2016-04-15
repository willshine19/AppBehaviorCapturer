/*
 * GetCallStateTelephonyManager.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "GetCallStateTelephonyManager.h"

GetCallStateTelephonyManager::GetCallStateTelephonyManager() {
	this->mApiDeclaration = *(new ApiDeclaration(
			"android/telephony/TelephonyManager", "getCallState", "()I", false,
			NULL, NULL, NULL));

}

GetCallStateTelephonyManager::~GetCallStateTelephonyManager() {
	// TODO Auto-generated destructor stub
}

bool GetCallStateTelephonyManager::parseResult(Object* obj) {
	char rs[20];
	int* ma;
	int i = 0;
	ma = (int*) obj;
	i = reinterpret_cast<int>(&ma[0]);
	sprintf(rs, "%d", i);
	StringObject* stringObjId = dvmCreateStringFromCstr(rs);
	char* resultString = dvmCreateCstrFromString(stringObjId);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(
			resultString);
	return true;
}
