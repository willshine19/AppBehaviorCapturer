/*
 * SendMultipartTextMessageSmsManager.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "SendMultipartTextMessageSmsManager.h"

SendMultipartTextMessageSmsManager::SendMultipartTextMessageSmsManager() {
	//modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/SmsManager",
			"sendMultipartTextMessage","(Ljava/lang/String;Ljava/lang/String;Ljava/util/ArrayList;Ljava/util/ArrayList;Ljava/util/ArrayList;)V",false,NULL,NULL,NULL));

}

SendMultipartTextMessageSmsManager::~SendMultipartTextMessageSmsManager() {
	// TODO Auto-generated destructor stub
}

