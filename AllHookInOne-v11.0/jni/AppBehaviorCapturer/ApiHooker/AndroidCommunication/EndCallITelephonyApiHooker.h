/*
 * EndCallITelephonyApiHooker.h
 *
 *  Created on: 2015-6-25
 *      Author: long
 */

#ifndef ENDCALLITELEPHONYAPIHOOKER_H_
#define ENDCALLITELEPHONYAPIHOOKER_H_

#include "../ApiHooker.h"

class EndCallITelephonyApiHooker: public ApiHooker {
public:
	EndCallITelephonyApiHooker();
	virtual ~EndCallITelephonyApiHooker();
	bool parseResult(Object* obj);
};

#endif /* ENDCALLITELEPHONYAPIHOOKER_H_ */
