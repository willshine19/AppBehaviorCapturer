/*
 * AddGpsStatusListenerLocationManager.h
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#ifndef ADDGPSSTATUSLISTENERLOCATIONMANAGER_H_
#define ADDGPSSTATUSLISTENERLOCATIONMANAGER_H_

#include "../ApiHooker.h"

/*
 *
 */
class AddGpsStatusListenerLocationManager: public ApiHooker {
public:
	AddGpsStatusListenerLocationManager();
	~AddGpsStatusListenerLocationManager();
	bool parseResult(Object* obj);
};

#endif /* ADDGPSSTATUSLISTENERLOCATIONMANAGER_H_ */
