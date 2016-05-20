/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "sendBroadcastApiHooker.h"

sendBroadcastApiHooker::sendBroadcastApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
			"sendBroadcast","(Landroid/content/Intent;)V",false,NULL,NULL,NULL));
}

sendBroadcastApiHooker::~sendBroadcastApiHooker() {
	// TODO Auto-generated destructor stub
}

