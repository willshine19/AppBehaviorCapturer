/*
 * GetSubscriberIdTelephonyManager.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef GETSUBSCRIBERIDTELEPHONYMANAGER_H_
#define GETSUBSCRIBERIDTELEPHONYMANAGER_H_

#include "../ApiHooker.h"

/*
 *
 */
class GetSubscriberIdTelephonyManager: public ApiHooker {
public:
	GetSubscriberIdTelephonyManager();
	~GetSubscriberIdTelephonyManager();
	bool parseResult(Object* obj);
};

#endif /* GETSUBSCRIBERIDTELEPHONYMANAGER_H_ */
