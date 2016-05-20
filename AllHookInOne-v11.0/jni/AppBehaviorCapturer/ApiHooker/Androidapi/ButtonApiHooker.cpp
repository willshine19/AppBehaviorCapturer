/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "ButtonApiHooker.h"

ButtonApiHooker::ButtonApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/Button",
			"<init>","(Landroid/content/Context;)V",false,NULL,NULL,NULL));
}

ButtonApiHooker::~ButtonApiHooker() {
	// TODO Auto-generated destructor stub
}

