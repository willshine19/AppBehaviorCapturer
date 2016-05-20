/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyDownApiHooker3.h"

onKeyDownApiHooker3::onKeyDownApiHooker3() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/VideoView",
			"onKeyDown","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyDownApiHooker3::~onKeyDownApiHooker3() {
	// TODO Auto-generated destructor stub
}

