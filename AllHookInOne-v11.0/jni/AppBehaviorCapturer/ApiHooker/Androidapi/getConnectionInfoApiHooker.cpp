/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getConnectionInfoApiHooker.h"

getConnectionInfoApiHooker::getConnectionInfoApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/net/wifi/WifiManager",
			"getConnectionInfo","()Landroid/net/wifi/WifiInfo;",false,NULL,NULL,NULL));
}

getConnectionInfoApiHooker::~getConnectionInfoApiHooker() {
	// TODO Auto-generated destructor stub
}

