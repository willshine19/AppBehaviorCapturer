/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "startApiHooker.h"

startApiHooker::startApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/media/MediaPlayer",
			"start","()V",false,NULL,NULL,NULL));
}

startApiHooker::~startApiHooker() {
	// TODO Auto-generated destructor stub
}

