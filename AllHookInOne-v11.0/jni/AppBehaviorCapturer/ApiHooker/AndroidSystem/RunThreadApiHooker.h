/*
 * RunThreadApiHooker.h
 *
 *  Created on: 2015-5-27
 *      Author: long
 */

#ifndef RUNTHREADAPIHOOKER_H_
#define RUNTHREADAPIHOOKER_H_

#include "../VoidApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"

class RunThreadApiHooker: public VoidApiHooker {
public:
	RunThreadApiHooker();
	virtual ~RunThreadApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* RUNTHREADAPIHOOKER_H_ */
