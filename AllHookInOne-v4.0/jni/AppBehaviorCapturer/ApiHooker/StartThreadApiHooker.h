/*
 * startThread.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef STARTTHREADAPIHOOKER_H_
#define STARTTHREADAPIHOOKER_H_

#include "VoidApiHooker.h"

class StartThreadApiHooker: public VoidApiHooker {

public:
	StartThreadApiHooker();
	virtual ~StartThreadApiHooker();
};

#endif /* STARTTHREAD_H_ */
