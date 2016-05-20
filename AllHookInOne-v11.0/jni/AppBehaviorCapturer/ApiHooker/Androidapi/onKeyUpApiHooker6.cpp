/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyUpApiHooker6.h"

onKeyUpApiHooker6::onKeyUpApiHooker6() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/ListView",
			"onKeyUp","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyUpApiHooker6::~onKeyUpApiHooker6() {
	// TODO Auto-generated destructor stub
}

