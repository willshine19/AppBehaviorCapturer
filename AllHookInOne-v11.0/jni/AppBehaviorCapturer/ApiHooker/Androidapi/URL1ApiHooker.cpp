/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "URL1ApiHooker.h"

URL1ApiHooker::URL1ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/net/URL",
			"<init>","(Ljava/net/URL;Ljava/lang/String;)V",false,NULL,NULL,NULL));
}

URL1ApiHooker::~URL1ApiHooker() {
	// TODO Auto-generated destructor stub
}

