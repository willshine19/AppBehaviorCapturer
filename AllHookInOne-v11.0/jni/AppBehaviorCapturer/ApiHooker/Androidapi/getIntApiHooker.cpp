/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getIntApiHooker.h"

getIntApiHooker::getIntApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/database/CursorWindow",
			"getInt","(II)I",false,NULL,NULL,NULL));
}

getIntApiHooker::~getIntApiHooker() {
	// TODO Auto-generated destructor stub
}

