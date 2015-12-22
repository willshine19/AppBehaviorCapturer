/*
 * OnStartServiceApiHooker.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef ONSTARTSERVICEAPIHOOKER_H_
#define ONSTARTSERVICEAPIHOOKER_H_

#include "../VoidApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"
#include "android_runtime/AndroidRuntime.h"
//#include "../../System/ApiHookerManager.h"

class OnStartServiceApiHooker: public VoidApiHooker {
public:
	OnStartServiceApiHooker();
	virtual ~OnStartServiceApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* ONSTARTSERVICEAPIHOOKER_H_ */
