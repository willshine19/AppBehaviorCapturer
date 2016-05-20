/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "ThreadApiHooker.h"

ThreadApiHooker::ThreadApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/lang/Thread",
			"<init>","()V",false,NULL,NULL,NULL));
}

ThreadApiHooker::~ThreadApiHooker() {
	// TODO Auto-generated destructor stub
}

