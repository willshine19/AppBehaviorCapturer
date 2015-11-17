/*
 * OnPauseActivityApiHooker.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef ONPAUSEACTIVITYAPIHOOKER_H_
#define ONPAUSEACTIVITYAPIHOOKER_H_

#include "../VoidApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"
#include "../../System/ApiHookerManager.h"//zds add
/*
 *
 */
class OnPauseActivityApiHooker: public VoidApiHooker {
public:
	OnPauseActivityApiHooker();
	virtual ~OnPauseActivityApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* ONPAUSEACTIVITYAPIHOOKER_H_ */
