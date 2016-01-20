/*
 * GetLine1NumberTelephonyManager.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef GETLINE1NUMBERTELEPHONYMANAGER_H_
#define GETLINE1NUMBERTELEPHONYMANAGER_H_

#include "../ApiHooker.h"

/*
 *
 */
class GetLine1NumberTelephonyManager: public ApiHooker {
public:
	GetLine1NumberTelephonyManager();
	~GetLine1NumberTelephonyManager();
	bool parseResult(Object* obj);
};

#endif /* GETLINE1NUMBERTELEPHONYMANAGER_H_ */
