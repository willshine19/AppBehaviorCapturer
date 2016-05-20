/*
 * GetSimSerialNumberTelephonyManager.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef GETSIMSERIALNUMBERTELEPHONYMANAGER_H_
#define GETSIMSERIALNUMBERTELEPHONYMANAGER_H_

#include "../ApiHooker.h"

/*
 *
 */
class GetSimSerialNumberTelephonyManager: public ApiHooker {
public:
	GetSimSerialNumberTelephonyManager();
	~GetSimSerialNumberTelephonyManager();
	bool parseResult(Object* obj);
};

#endif /* GETSIMSERIALNUMBERTELEPHONYMANAGER_H_ */
