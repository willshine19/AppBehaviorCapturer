/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "Socket1ApiHooker.h"

Socket1ApiHooker::Socket1ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/net/Socket",
			"<init>","(Ljava/net/Proxy;)V",false,NULL,NULL,NULL));
}

Socket1ApiHooker::~Socket1ApiHooker() {
	// TODO Auto-generated destructor stub
}

