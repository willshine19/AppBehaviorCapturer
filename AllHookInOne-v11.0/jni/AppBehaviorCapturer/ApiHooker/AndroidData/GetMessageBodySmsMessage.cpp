/*
 * GetMessageBodySmsMessage.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "GetMessageBodySmsMessage.h"

GetMessageBodySmsMessage::GetMessageBodySmsMessage() {
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/gsm/SmsMessage",
			"getMessageBody","()Ljava/lang/String;",false,NULL,NULL,NULL));


}

GetMessageBodySmsMessage::~GetMessageBodySmsMessage() {
	// TODO Auto-generated destructor stub
}

