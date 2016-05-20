/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyUpApiHooker7.h"

onKeyUpApiHooker7::onKeyUpApiHooker7() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Dialog",
			"onKeyUp","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyUpApiHooker7::~onKeyUpApiHooker7() {
	// TODO Auto-generated destructor stub
}

