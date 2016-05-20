/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "encodeApiHooker.h"

encodeApiHooker::encodeApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/net/URLEncoder",
			"encode","(Ljava/lang/String;)Ljava/lang/String;",true,NULL,NULL,NULL));
}

encodeApiHooker::~encodeApiHooker() {
	// TODO Auto-generated destructor stub
}

