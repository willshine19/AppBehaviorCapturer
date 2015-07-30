/*
 * RunThreadApiHooker.cpp
 *
 *  Created on: 2015-5-27
 *      Author: long
 */

#include "RunThreadApiHooker.h"

RunThreadApiHooker::RunThreadApiHooker() {
	// TODO Auto-generated constructor stub
	this->mApiDeclaration = *(new ApiDeclaration("java/lang/Thread","run","()V",
			false,NULL,NULL,NULL));
}

RunThreadApiHooker::~RunThreadApiHooker() {
	// TODO Auto-generated destructor stub
}

