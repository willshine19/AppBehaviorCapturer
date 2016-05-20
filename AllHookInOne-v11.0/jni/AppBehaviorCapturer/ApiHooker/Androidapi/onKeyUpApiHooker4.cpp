/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyUpApiHooker4.h"

onKeyUpApiHooker4::onKeyUpApiHooker4() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/webkit/WebView",
			"onKeyUp","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyUpApiHooker4::~onKeyUpApiHooker4() {
	// TODO Auto-generated destructor stub
}

