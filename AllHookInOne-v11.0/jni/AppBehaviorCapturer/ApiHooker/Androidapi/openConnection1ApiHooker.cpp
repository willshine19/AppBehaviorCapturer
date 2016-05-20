/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "openConnection1ApiHooker.h"

openConnection1ApiHooker::openConnection1ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/net/URL",
			"openConnection","()Ljava/net/URLConnection;",false,NULL,NULL,NULL));
}

openConnection1ApiHooker::~openConnection1ApiHooker() {
	// TODO Auto-generated destructor stub
}

