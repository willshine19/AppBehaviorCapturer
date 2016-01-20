/*
 * GetDefaultSensorSensorManager.h
 *
 *  Created on: 2015-6-17
 *      Author: sang
 */

#ifndef GETDEFAULTSENSORSENSORMANAGER_H_
#define GETDEFAULTSENSORSENSORMANAGER_H_

#include "../ApiHooker.h"

/*
 *
 */
class GetDefaultSensorSensorManager: public ApiHooker {
public:
	GetDefaultSensorSensorManager();
	~GetDefaultSensorSensorManager();
	bool parseResult(Object* obj);
};

#endif /* GETDEFAULTSENSORSENSORMANAGER_H_ */
