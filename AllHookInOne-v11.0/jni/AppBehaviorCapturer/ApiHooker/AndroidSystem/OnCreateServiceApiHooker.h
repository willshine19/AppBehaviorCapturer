/*
 * OnCreateServiceApiHooker.h
 *
 *  Created on: 2015-10-29
 *      Author: zds
 */

#ifndef ONCREATSERVICEAPIHOOKER_H_
#define ONCREATSERVICEAPIHOOKER_H_

#include "../VoidApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"
#include "android_runtime/AndroidRuntime.h"
//#include "../../System/ApiHookerManager.h"

class OnCreateServiceApiHooker: public VoidApiHooker {
public:
	OnCreateServiceApiHooker();
	virtual ~OnCreateServiceApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* ONCREATSERVICEAPIHOOKER_H_ */
