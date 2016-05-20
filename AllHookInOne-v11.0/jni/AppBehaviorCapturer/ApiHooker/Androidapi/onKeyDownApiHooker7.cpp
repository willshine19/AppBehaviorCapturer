/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyDownApiHooker7.h"

onKeyDownApiHooker7::onKeyDownApiHooker7() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/AbsListView",
			"onKeyDown","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyDownApiHooker7::~onKeyDownApiHooker7() {
	// TODO Auto-generated destructor stub
}

