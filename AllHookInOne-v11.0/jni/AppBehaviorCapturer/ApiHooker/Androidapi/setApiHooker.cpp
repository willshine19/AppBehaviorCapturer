/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "setApiHooker.h"

setApiHooker::setApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/text/TextPaint",
			"set","(Landroid/text/TextPaint;)V",false,NULL,NULL,NULL));
}

setApiHooker::~setApiHooker() {
	// TODO Auto-generated destructor stub
}

