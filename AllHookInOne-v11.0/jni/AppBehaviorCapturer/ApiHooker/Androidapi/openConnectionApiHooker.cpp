/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "openConnectionApiHooker.h"

openConnectionApiHooker::openConnectionApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/net/URL",
			"openConnection","(Ljava/net/Proxy;)Ljava/net/URLConnection;",false,NULL,NULL,NULL));
}

openConnectionApiHooker::~openConnectionApiHooker() {
	// TODO Auto-generated destructor stub
}

