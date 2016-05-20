/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getSystemServiceApiHooker.h"

getSystemServiceApiHooker::getSystemServiceApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/ContextThemeWrapper",
			"getSystemService","(Ljava/lang/String;)Ljava/lang/Object;",false,NULL,NULL,NULL));
}

getSystemServiceApiHooker::~getSystemServiceApiHooker() {
	// TODO Auto-generated destructor stub
}

