/*
 * OnCreateActivityApiHooker.h
 *
 *  Created on: 2015-5-12
 *      Author: long
 */

#ifndef ONCREATACTIVITYAPIHOOKER_H_
#define ONCREATACTIVITYAPIHOOKER_H_

#include "../VoidApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"
#include "android_runtime/AndroidRuntime.h"
#include "../../System/ApiHookerManager.h"//zds add

class OnCreateActivityApiHooker:public VoidApiHooker{
public:
	OnCreateActivityApiHooker();
	virtual ~OnCreateActivityApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* ONCREATACTIVITYAPIHOOKER_H_ */
