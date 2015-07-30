/*
 * SendDataMessageSmsManager.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "SendDataMessageSmsManager.h"

SendDataMessageSmsManager::SendDataMessageSmsManager() {
	//modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/SmsManager",
			"sendDataMessage","(Ljava/lang/String;Ljava/lang/String;S[BLandroid/app/PendingIntent;Landroid/app/PendingIntent;)V",false,NULL,NULL,NULL));

}

SendDataMessageSmsManager::~SendDataMessageSmsManager() {
	// TODO Auto-generated destructor stub
}

