/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getStringApiHooker.h"

getStringApiHooker::getStringApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/database/CursorWindow",
			"getString","(II)Ljava/lang/String;",false,NULL,NULL,NULL));
}

getStringApiHooker::~getStringApiHooker() {
	// TODO Auto-generated destructor stub
}

