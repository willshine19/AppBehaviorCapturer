/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "addListenerApiHooker.h"

addListenerApiHooker::addListenerApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/animation/ValueAnimator",
			"addUpdateListener","(Landroid/animation/ValueAnimator$AnimatorUpdateListener;)V",false,NULL,NULL,NULL));
}

addListenerApiHooker::~addListenerApiHooker() {
	// TODO Auto-generated destructor stub
}

