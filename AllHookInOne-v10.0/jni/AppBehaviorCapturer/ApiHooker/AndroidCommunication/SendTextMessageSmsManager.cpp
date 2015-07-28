/*
 * SendTextMessageSmsManager.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "SendTextMessageSmsManager.h"

SendTextMessageSmsManager::SendTextMessageSmsManager() {
	//modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/SmsManager",
			"sendTextMessage","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Landroid/app/PendingIntent;Landroid/app/PendingIntent;)V",false,NULL,NULL,NULL));

}

SendTextMessageSmsManager::~SendTextMessageSmsManager() {
	// TODO Auto-generated destructor stub
}

