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
<<<<<<< HEAD
#include "../../System/ThreadMap.h"
//#include <unordered_map>
#include <pthread.h>
=======
>>>>>>> 5925c92b2d953bfa3a997e46571c8c3e4b2393da

class RunThreadApiHooker: public VoidApiHooker {
public:
	RunThreadApiHooker();
	virtual ~RunThreadApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* RUNTHREADAPIHOOKER_H_ */
