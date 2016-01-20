/*
 * QueryContentResolverApiHooker.h
 *
 *  Created on: 2015-6-16
 *      Author: long
 */

#ifndef QUERYCONTENTRESOLVERAPIHOOKER_H_
#define QUERYCONTENTRESOLVERAPIHOOKER_H_

#include "../ApiHooker.h"

class QueryContentResolverApiHooker: public ApiHooker {
public:
	QueryContentResolverApiHooker();
	virtual ~QueryContentResolverApiHooker();
	bool parseResult(Object* obj);
};

#endif /* QUERYCONTENTRESOLVERAPIHOOKER_H_ */
