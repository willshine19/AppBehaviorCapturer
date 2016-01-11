/*
 * GetMacAddressWifiInfoApiHooker.h
 *
 *  Created on: 2015-5-13
 *      Author: long
 */

#ifndef GETMACADDRESSWIFIINFOAPIHOOKER_H_
#define GETMACADDRESSWIFIINFOAPIHOOKER_H_

#include "../ApiHooker.h"

class GetMacAddressWifiInfoApiHooker: public ApiHooker {
public:
	GetMacAddressWifiInfoApiHooker();
	virtual ~GetMacAddressWifiInfoApiHooker();
	bool parseResult(Object* obj);
};

#endif /* GETMACADDRESSWIFIINFOAPIHOOKER_H_ */
