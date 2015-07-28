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

} /* namespace std */
