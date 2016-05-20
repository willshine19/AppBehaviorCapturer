/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getInstanceApiHooker.h"

getInstanceApiHooker::getInstanceApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/webkit/CookieManager",
			"getInstance","()Landroid/webkit/CookieManager;",true,NULL,NULL,NULL));
}

getInstanceApiHooker::~getInstanceApiHooker() {
	// TODO Auto-generated destructor stub
}

