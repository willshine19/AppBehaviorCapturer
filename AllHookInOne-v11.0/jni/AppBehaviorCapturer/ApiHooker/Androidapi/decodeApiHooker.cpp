/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "decodeApiHooker.h"

decodeApiHooker::decodeApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/net/URLDecoder",
			"decode","(Ljava/lang/String;)Ljava/lang/String;",true,NULL,NULL,NULL));
}

decodeApiHooker::~decodeApiHooker() {
	// TODO Auto-generated destructor stub
}

