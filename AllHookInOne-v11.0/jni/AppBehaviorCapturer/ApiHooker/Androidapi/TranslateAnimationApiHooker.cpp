/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "TranslateAnimationApiHooker.h"

TranslateAnimationApiHooker::TranslateAnimationApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/animation/TranslateAnimation",
			"<init>","(Landroid/content/Context;Landroid/util/AttributeSet;)V",false,NULL,NULL,NULL));
}

TranslateAnimationApiHooker::~TranslateAnimationApiHooker() {
	// TODO Auto-generated destructor stub
}

