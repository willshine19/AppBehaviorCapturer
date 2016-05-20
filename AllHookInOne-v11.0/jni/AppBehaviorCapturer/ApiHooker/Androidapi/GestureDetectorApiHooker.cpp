/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "GestureDetectorApiHooker.h"

GestureDetectorApiHooker::GestureDetectorApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/GestureDetector",
			"<init>","(Landroid/view/GestureDetector$OnGestureListener;Landroid/os/Handler;)V",false,NULL,NULL,NULL));
}

GestureDetectorApiHooker::~GestureDetectorApiHooker() {
	// TODO Auto-generated destructor stub
}

