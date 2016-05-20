/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyDownApiHooker4.h"

onKeyDownApiHooker4::onKeyDownApiHooker4() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/webkit/WebView",
			"onKeyDown","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyDownApiHooker4::~onKeyDownApiHooker4() {
	// TODO Auto-generated destructor stub
}

