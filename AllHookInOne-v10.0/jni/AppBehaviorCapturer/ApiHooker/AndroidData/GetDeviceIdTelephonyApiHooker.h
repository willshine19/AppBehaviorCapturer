/*
 * GetDeviceIdTelephonyApiHooker.h
 *
 *  Created on: 2015-5-27
 *      Author: long
 */

#ifndef GETDEVICEIDTELEPHONYAPIHOOKER_H_
#define GETDEVICEIDTELEPHONYAPIHOOKER_H_

#include "../VoidApiHooker.h"

namespace std {

class GetDeviceIdTelephonyApiHooker: public VoidApiHooker {
public:
	GetDeviceIdTelephonyApiHooker();
	virtual ~GetDeviceIdTelephonyApiHooker();
};

} /* namespace std */
#endif /* GETDEVICEIDTELEPHONYAPIHOOKER_H_ */
