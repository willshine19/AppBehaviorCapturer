/*
 * onStartCommandServiceApiHooker.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef ONSTARTCOMMANDSERVICEAPIHOOKER_H_
#define ONSTARTCOMMANDSERVICEAPIHOOKER_H_

#include "../ApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"
#include "android_runtime/AndroidRuntime.h"
//#include "../../System/ApiHookerManager.h"

class onStartCommandServiceApiHooker: public ApiHooker {
public:
	onStartCommandServiceApiHooker();
	virtual ~onStartCommandServiceApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* ONSTARTCOMMANDSERVICEAPIHOOKER_H_ */
