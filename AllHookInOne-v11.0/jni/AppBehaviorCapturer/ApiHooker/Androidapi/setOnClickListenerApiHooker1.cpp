/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "setOnClickListenerApiHooker1.h"

setOnClickListenerApiHooker1::setOnClickListenerApiHooker1() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/AutoCompleteTextView",
			"setOnClickListener","(Landroid/view/View$OnClickListener;)V",false,NULL,NULL,NULL));
}

setOnClickListenerApiHooker1::~setOnClickListenerApiHooker1() {
	// TODO Auto-generated destructor stub
}

