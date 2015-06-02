/*
 * RunThreadApiHooker.h
 *
 *  Created on: 2015-5-27
 *      Author: long
 */

#ifndef RUNTHREADAPIHOOKER_H_
#define RUNTHREADAPIHOOKER_H_

#include "VoidApiHooker.h"

class RunThreadApiHooker: public VoidApiHooker {
public:
	RunThreadApiHooker();
	virtual ~RunThreadApiHooker();
};

#endif /* RUNTHREADAPIHOOKER_H_ */
