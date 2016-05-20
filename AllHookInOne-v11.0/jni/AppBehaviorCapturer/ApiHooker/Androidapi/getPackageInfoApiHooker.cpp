/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getPackageInfoApiHooker.h"

getPackageInfoApiHooker::getPackageInfoApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/content/pm/PackageManager",
			"getPackageInfo","(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;",false,NULL,NULL,NULL));
}

getPackageInfoApiHooker::~getPackageInfoApiHooker() {
	// TODO Auto-generated destructor stub
}

