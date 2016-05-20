/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyDownApiHooker6.h"

onKeyDownApiHooker6::onKeyDownApiHooker6() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/ListView",
			"onKeyDown","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyDownApiHooker6::~onKeyDownApiHooker6() {
	// TODO Auto-generated destructor stub
}

