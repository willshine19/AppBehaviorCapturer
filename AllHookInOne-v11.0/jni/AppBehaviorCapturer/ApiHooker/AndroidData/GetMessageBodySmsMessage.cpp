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

bool GetMessageBodySmsMessage::parseResult(Object* obj) {
	StringObject* stringObjId = (StringObject*) obj;
	char* resultString = dvmCreateCstrFromString(stringObjId);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(resultString);
	return true;
}
