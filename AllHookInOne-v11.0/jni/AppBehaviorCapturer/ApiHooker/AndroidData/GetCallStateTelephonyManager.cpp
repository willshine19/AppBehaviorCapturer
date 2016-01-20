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
//	char rs[30];
//	char *mystr = (char*)malloc(sizeof(rs));
//	int* m=(int*)obj;
//	sprintf(rs, "%d", *m);
//	sprintf(mystr, "%d", *m);
//	LOGD("[返回值解析char*] -> %s", mystr);
//	LOGD("[返回值解析char[30]] -> %s", rs);
	LOGD("[返回值解析 d] -> %d", (int*)obj);
////	LOGD("[返回值解析] -> %s", resultString);
//	const char* className = "java/lang/Integer";
//	char* resultString = parseObjectToString(obj, className);
//	LOGD("[返回值解析tostring] -> %s", resultString);
	return true;
}
/*bool GetCallStateTelephonyManager::parseResult(Object* obj) {
	const char* className = "java/lang/Integer";
	char* resultString = parseObjectToString(obj, className);
	LOGD("[返回值解析] -> %s", resultString);
	return true;
}*/
