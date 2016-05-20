/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "AnimationApiHooker.h"

AnimationApiHooker::AnimationApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/animation/Animation",
			"<init>","()V",false,NULL,NULL,NULL));
}

AnimationApiHooker::~AnimationApiHooker() {
	// TODO Auto-generated destructor stub
}

