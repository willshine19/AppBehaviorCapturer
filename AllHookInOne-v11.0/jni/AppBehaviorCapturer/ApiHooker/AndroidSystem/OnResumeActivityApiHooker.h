/*
 * OnResumeActivityApiHooker.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef ONRESUMEACTIVITYAPIHOOKER_H_
#define ONRESUMEACTIVITYAPIHOOKER_H_

#include "../VoidApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"
//#include "android_runtime/AndroidRuntime.h"
#include "../../System/ApiHookerManager.h"//zds add
#include "../../System/ThreadMap.h"
#include <pthread.h>
/*
 *
 */
class OnResumeActivityApiHooker: public VoidApiHooker {
public:
	OnResumeActivityApiHooker();
	virtual ~OnResumeActivityApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* ONRESUMEACTIVITYAPIHOOKER_H_ */
