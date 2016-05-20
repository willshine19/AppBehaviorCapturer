/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "prepareApiHooker.h"

prepareApiHooker::prepareApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/media/MediaRecorder",
			"prepare","()V",false,NULL,NULL,NULL));
}

prepareApiHooker::~prepareApiHooker() {
	// TODO Auto-generated destructor stub
}

