/*
 * OnStartActivityApiHooker.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef ONSTARTACTIVITYAPIHOOKER_H_
#define ONSTARTACTIVITYAPIHOOKER_H_

#include "../VoidApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"
#include "../../System/ApiHookerManager.h"//zds add

/*
 *
 */
class OnStartActivityApiHooker: public VoidApiHooker {
public:
	OnStartActivityApiHooker();
	virtual ~OnStartActivityApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* ONSTARTACTIVITYAPIHOOKER_H_ */
