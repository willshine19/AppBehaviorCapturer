/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "onKeyDown1ApiHooker.h"

onKeyDown1ApiHooker::onKeyDown1ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"onKeyDown","(ILandroid/view/KeyEvent;)Z",false,NULL,NULL,NULL));
}

onKeyDown1ApiHooker::~onKeyDown1ApiHooker() {
	// TODO Auto-generated destructor stub
}

