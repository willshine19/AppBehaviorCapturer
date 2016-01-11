/*
 * GetDeviceIdTelephonyApiHooker.cpp
 *
 *  Created on: 2015-5-27
 *      Author: long
 */

#include "GetDeviceIdTelephonyApiHooker.h"

namespace std {

GetDeviceIdTelephonyApiHooker::GetDeviceIdTelephonyApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/TelephonyManager",
			"getDeviceId","()Ljava/lang/String;",false,NULL,NULL,NULL));

}

GetDeviceIdTelephonyApiHooker::~GetDeviceIdTelephonyApiHooker() {
	// TODO Auto-generated destructor stub
}
bool GetDeviceIdTelephonyApiHooker::parseResult(Object* obj) {
	StringObject* stringObjId = (StringObject*) obj;
	char* resultString = dvmCreateCstrFromString(stringObjId);
	LOGD("[返回值解析] -> %s", resultString);
	return true;
}
} /* namespace std */
