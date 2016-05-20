/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "WindowApiHooker.h"

WindowApiHooker::WindowApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/Window",
			"<init>","(Landroid/content/Context;)V",false,NULL,NULL,NULL));
}

WindowApiHooker::~WindowApiHooker() {
	// TODO Auto-generated destructor stub
}

