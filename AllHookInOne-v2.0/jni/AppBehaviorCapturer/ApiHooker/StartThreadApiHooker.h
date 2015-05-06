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
/*	CollectedApiInfo mCollectedApiInfo;
	MethodDeclaration mMethodDeclaration;*/
public:
	StartThreadApiHooker();
	StartThreadApiHooker(ApiDeclaration* apiDeclaration,CollectedApiInfo* collectedApiInfo);
	virtual ~StartThreadApiHooker();

	static void method_handler();
};

#endif /* STARTTHREAD_H_ */
