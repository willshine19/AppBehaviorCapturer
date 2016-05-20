/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyUpApiHooker3.h"

onKeyUpApiHooker3::onKeyUpApiHooker3() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/AbsListView",
			"onKeyUp","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyUpApiHooker3::~onKeyUpApiHooker3() {
	// TODO Auto-generated destructor stub
}

