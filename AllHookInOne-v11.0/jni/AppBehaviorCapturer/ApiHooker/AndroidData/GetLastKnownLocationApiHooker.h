/*
 * GetLastKnownLocationApiHooker.h
 *
 *  Created on: 2015-5-27
 *      Author: long
 */

#ifndef GETLASTKNOWNLOCATIONAPIHOOKER_H_
#define GETLASTKNOWNLOCATIONAPIHOOKER_H_

#include "../ApiHooker.h"
#include "android_runtime/AndroidRuntime.h"

class GetLastKnownLocationApiHooker: public ApiHooker {
public:
	GetLastKnownLocationApiHooker();
	virtual ~GetLastKnownLocationApiHooker();
	bool parseParameter(const u4* args);
	bool parseResult(Object* obj);
};

#endif /* GETLASTKNOWNLOCATIONAPIHOOKER_H_ */
