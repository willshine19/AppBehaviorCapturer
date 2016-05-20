/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "loadUrlApiHooker.h"

loadUrlApiHooker::loadUrlApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/webkit/WebView",
			"loadUrl","(Ljava/lang/String;)V",false,NULL,NULL,NULL));
}

loadUrlApiHooker::~loadUrlApiHooker() {
	// TODO Auto-generated destructor stub
}

