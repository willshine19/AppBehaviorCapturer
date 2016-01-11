/*
 * InsertContentResolverApiHooker.h
 *
 *  Created on: 2015-6-16
 *      Author: long
 */

#ifndef INSERTCONTENTRESOLVERAPIHOOKER_H_
#define INSERTCONTENTRESOLVERAPIHOOKER_H_

#include "../ApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"
#include "android_runtime/AndroidRuntime.h"

class InsertContentResolverApiHooker: public ApiHooker {
public:
	InsertContentResolverApiHooker();
	virtual ~InsertContentResolverApiHooker();
	bool parseParameter(const u4* args);
	bool parseResult(Object* obj);
};

#endif /* INSERTCONTENTRESOLVERAPIHOOKER_H_ */
