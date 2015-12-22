/*
 * OnStopActivityApiHooker.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef ONSTOPACTIVITYAPIHOOKER_H_
#define ONSTOPACTIVITYAPIHOOKER_H_

#include "../VoidApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"
#include "../../System/ApiHookerManager.h"//zds add

/*
 *
 */
class OnStopActivityApiHooker: public VoidApiHooker {
public:
	OnStopActivityApiHooker();
	virtual ~OnStopActivityApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* ONSTOPACTIVITYAPIHOOKER_H_ */
