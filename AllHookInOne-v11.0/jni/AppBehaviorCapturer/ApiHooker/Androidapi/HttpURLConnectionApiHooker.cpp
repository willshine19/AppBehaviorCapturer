/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "HttpURLConnectionApiHooker.h"

HttpURLConnectionApiHooker::HttpURLConnectionApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/net/HttpURLConnection",
			"<init>","(Ljava/net/URL;)V",false,NULL,NULL,NULL));
}

HttpURLConnectionApiHooker::~HttpURLConnectionApiHooker() {
	// TODO Auto-generated destructor stub
}

