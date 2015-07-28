/*
 * StartThreadApiHooker.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "StartThreadApiHooker.h"

StartThreadApiHooker::StartThreadApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("java/lang/Thread","start","()V",
			false,NULL,NULL,NULL));
//	this->mCollectedApiInfo = *(new CollectedApiInfo());
}

StartThreadApiHooker::~StartThreadApiHooker() {
	// TODO Auto-generated destructor stub
}

