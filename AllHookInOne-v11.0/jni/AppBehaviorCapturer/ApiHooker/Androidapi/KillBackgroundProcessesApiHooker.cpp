/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "KillBackgroundProcessesApiHooker.h"

KillBackgroundProcessesApiHooker::KillBackgroundProcessesApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/app/ActivityManager",
			"killBackgroundProcesses","(Ljava/lang/String;)V",false,NULL,NULL,NULL));
}

KillBackgroundProcessesApiHooker::~KillBackgroundProcessesApiHooker() {
	// TODO Auto-generated destructor stub
}

