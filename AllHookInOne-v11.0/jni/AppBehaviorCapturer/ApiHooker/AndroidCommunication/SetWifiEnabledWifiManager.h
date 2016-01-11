/*
 * SetWifiEnabledWifiManager.h
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#ifndef SETWIFIENABLEDWIFIMANAGER_H_
#define SETWIFIENABLEDWIFIMANAGER_H_

#include "../ApiHooker.h"

/*
 *
 */
class SetWifiEnabledWifiManager: public ApiHooker {
public:
	SetWifiEnabledWifiManager();
	~SetWifiEnabledWifiManager();
	bool parseResult(Object* obj);
};

#endif /* SETWIFIENABLEDWIFIMANAGER_H_ */
