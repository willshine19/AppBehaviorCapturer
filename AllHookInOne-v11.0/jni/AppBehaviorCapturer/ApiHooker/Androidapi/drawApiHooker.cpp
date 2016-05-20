/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "drawApiHooker.h"

drawApiHooker::drawApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/graphics/drawable/DrawableContainer",
			"draw","(Landroid/graphics/Canvas;)V",false,NULL,NULL,NULL));
}

drawApiHooker::~drawApiHooker() {
	// TODO Auto-generated destructor stub
}

