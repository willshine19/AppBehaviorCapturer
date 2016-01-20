/*
 * GetDeviceIdTelephonyApiHooker.h
 *
 *  Created on: 2015-5-27
 *      Author: long
 */

#ifndef GETDEVICEIDTELEPHONYAPIHOOKER_H_
#define GETDEVICEIDTELEPHONYAPIHOOKER_H_

#include "../ApiHooker.h"

namespace std {

class GetDeviceIdTelephonyApiHooker: public ApiHooker {
public:
	GetDeviceIdTelephonyApiHooker();
	virtual ~GetDeviceIdTelephonyApiHooker();
	bool parseResult(Object* obj);
};

} /* namespace std */
#endif /* GETDEVICEIDTELEPHONYAPIHOOKER_H_ */
