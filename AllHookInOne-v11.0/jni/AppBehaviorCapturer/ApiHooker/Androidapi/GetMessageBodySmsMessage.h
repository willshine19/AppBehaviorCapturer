/*
 * GetMessageBodySmsMessage.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef GETMESSAGEBODYSMSMESSAGE_H_
#define GETMESSAGEBODYSMSMESSAGE_H_

#include "../ApiHooker.h"

/*
 *
 */
class GetMessageBodySmsMessage: public ApiHooker {
public:
	GetMessageBodySmsMessage();
	~GetMessageBodySmsMessage();
//	bool parseResult(Object* obj);
};

#endif /* GETMESSAGEBODYSMSMESSAGE_H_ */
