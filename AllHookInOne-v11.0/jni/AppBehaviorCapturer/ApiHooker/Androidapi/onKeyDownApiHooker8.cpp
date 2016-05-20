/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyDownApiHooker8.h"

onKeyDownApiHooker8::onKeyDownApiHooker8() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/SearchView",
			"onKeyDown","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyDownApiHooker8::~onKeyDownApiHooker8() {
	// TODO Auto-generated destructor stub
}

