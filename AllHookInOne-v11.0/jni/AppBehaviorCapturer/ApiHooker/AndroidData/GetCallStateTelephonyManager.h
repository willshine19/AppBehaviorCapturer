/*
 * GetCallStateTelephonyManager.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef GETCALLSTATETELEPHONYMANAGER_H_
#define GETCALLSTATETELEPHONYMANAGER_H_

#include "../ApiHooker.h"

/*
 *
 */
class GetCallStateTelephonyManager: public ApiHooker {
public:
	GetCallStateTelephonyManager();
	~GetCallStateTelephonyManager();
	bool parseResult(Object* obj);
};

#endif /* GETCALLSTATETELEPHONYMANAGER_H_ */
