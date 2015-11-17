/*
 * OnDestroyActivityApiHooker.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef ONDESTROYACTIVITYAPIHOOKER_H_
#define ONDESTROYACTIVITYAPIHOOKER_H_

#include "../VoidApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"
#include "../../System/ApiHookerManager.h"//zds add
/*
 *
 */
class OnDestroyActivityApiHooker: public VoidApiHooker {
public:
	OnDestroyActivityApiHooker();
	virtual ~OnDestroyActivityApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* ONDESTROYACTIVITYAPIHOOKER_H_ */
