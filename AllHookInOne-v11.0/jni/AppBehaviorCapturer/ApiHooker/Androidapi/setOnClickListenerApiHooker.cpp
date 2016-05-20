/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "setOnClickListenerApiHooker.h"

setOnClickListenerApiHooker::setOnClickListenerApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/View",
			"setOnClickListener","(Landroid/view/View$OnClickListener;)V",false,NULL,NULL,NULL));
}

setOnClickListenerApiHooker::~setOnClickListenerApiHooker() {
	// TODO Auto-generated destructor stub
}

