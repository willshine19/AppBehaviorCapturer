/*
 * GetLastKnownLocationApiHooker.cpp
 *
 *  Created on: 2015-5-27
 *      Author: long
 */

#include "GetLastKnownLocationApiHooker.h"
using namespace android;
GetLastKnownLocationApiHooker::GetLastKnownLocationApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/location/LocationManager",
			"getLastKnownLocation","(Ljava/lang/String;)Landroid/location/Location;",false,NULL,NULL,NULL));

}

GetLastKnownLocationApiHooker::~GetLastKnownLocationApiHooker() {
	// TODO Auto-generated destructor stub
}
bool GetLastKnownLocationApiHooker::parseParameter(const u4* args){
	StringObject* temp = (StringObject*) args[1];
	char* paramString = dvmCreateCstrFromString(temp);
	LOGD("paramString is %s",paramString);
	return true;
}
bool GetLastKnownLocationApiHooker::parseResult(Object* obj) {
	const char* className = "android/location/Location";
	char* resultString = parseObjectToString(obj, className);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(resultString);
	return true;
}
