/*
 * OnCreateApplicationApiHooker.h
 *
 *  Created on: 2015-10-29
 *      Author: zds
 */

#ifndef ONCREATAPPLICATIONAPIHOOKER_H_
#define ONCREATAPPLICATIONAPIHOOKER_H_

#include "../VoidApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"
#include "android_runtime/AndroidRuntime.h"
//#include "../../System/ApiHookerManager.h"

class OnCreateApplicationApiHooker: public VoidApiHooker {
public:
	OnCreateApplicationApiHooker();
	virtual ~OnCreateApplicationApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* ONCREATAPPLICATIONAPIHOOKER_H_ */
