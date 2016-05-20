/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onLongPressApiHooker2.h"

onLongPressApiHooker2::onLongPressApiHooker2() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/inputmethodservice/KeyboardView",
			"onLongPress","(Landroid/inputmethodservice/Keyboard$Key;)Z",false,NULL,NULL,NULL));
}

onLongPressApiHooker2::~onLongPressApiHooker2() {
	// TODO Auto-generated destructor stub
}

