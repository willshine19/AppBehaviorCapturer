/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "SocketApiHooker.h"

SocketApiHooker::SocketApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/net/Socket",
			"<init>","()V",false,NULL,NULL,NULL));
}

SocketApiHooker::~SocketApiHooker() {
	// TODO Auto-generated destructor stub
}

