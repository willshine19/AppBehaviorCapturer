/*
 * OnRestartActivityApiHooker.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef ONRESTARTACTIVITYAPIHOOKER_H_
#define ONRESTARTACTIVITYAPIHOOKER_H_

#include "../VoidApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"
#include "../../System/ApiHookerManager.h"//zds add
/*
 *
 */
class OnRestartActivityApiHooker: public VoidApiHooker {
public:
	OnRestartActivityApiHooker();
	virtual ~OnRestartActivityApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* ONRESTARTACTIVITYAPIHOOKER_H_ */
