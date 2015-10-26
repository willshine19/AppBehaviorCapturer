/*
 * startThread.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef STARTTHREADAPIHOOKER_H_
#define STARTTHREADAPIHOOKER_H_

#include "../VoidApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"

class StartThreadApiHooker: public VoidApiHooker{

public:
	StartThreadApiHooker();
	virtual ~StartThreadApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* STARTTHREAD_H_ */
