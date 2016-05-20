/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "RectApiHooker.h"

RectApiHooker::RectApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/graphics/Rect",
			"<init>","()V",false,NULL,NULL,NULL));
}

RectApiHooker::~RectApiHooker() {
	// TODO Auto-generated destructor stub
}

