/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "sendTextMessageApiHooker.h"

sendTextMessageApiHooker::sendTextMessageApiHooker() {
	// modified by lwl
	this->mApiDeclaration =
			*(new ApiDeclaration("android/telephony/SmsManager",
					"sendTextMessage",
					"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Landroid/app/PendingIntent;Landroid/app/PendingIntent;)V",
					false, NULL, NULL, NULL));
}

sendTextMessageApiHooker::~sendTextMessageApiHooker() {
	// TODO Auto-generated destructor stub
}

