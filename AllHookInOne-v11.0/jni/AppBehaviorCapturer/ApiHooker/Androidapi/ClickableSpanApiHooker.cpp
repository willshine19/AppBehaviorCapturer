/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "ClickableSpanApiHooker.h"

ClickableSpanApiHooker::ClickableSpanApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/text/style/ClickableSpan",
			"<init>","()V",false,NULL,NULL,NULL));
}

ClickableSpanApiHooker::~ClickableSpanApiHooker() {
	// TODO Auto-generated destructor stub
}

