/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "execApiHooker.h"

execApiHooker::execApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/lang/Runtime",
			"exec","(Ljava/lang/String;[Ljava/lang/String;Ljava/io/File;)Ljava/lang/Process;",false,NULL,NULL,NULL));
}

execApiHooker::~execApiHooker() {
	// TODO Auto-generated destructor stub
}

