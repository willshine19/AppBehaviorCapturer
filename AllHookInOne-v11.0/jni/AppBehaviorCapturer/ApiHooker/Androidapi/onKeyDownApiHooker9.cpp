/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyDownApiHooker9.h"

onKeyDownApiHooker9::onKeyDownApiHooker9() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Dialog",
			"onKeyDown","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyDownApiHooker9::~onKeyDownApiHooker9() {
	// TODO Auto-generated destructor stub
}

