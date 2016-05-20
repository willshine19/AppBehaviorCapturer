/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "sendBroadcast2ApiHooker.h"

sendBroadcast2ApiHooker::sendBroadcast2ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
			"sendBroadcast","(Landroid/content/Intent;Ljava/lang/String;)V",false,NULL,NULL,NULL));
}

sendBroadcast2ApiHooker::~sendBroadcast2ApiHooker() {
	// TODO Auto-generated destructor stub
}

