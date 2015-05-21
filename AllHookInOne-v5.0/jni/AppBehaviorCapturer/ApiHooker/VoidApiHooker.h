/*
 * VoidApiHooker.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef VOIDAPIHOOKER_H_
#define VOIDAPIHOOKER_H_

#include "ApiHooker.h"

class VoidApiHooker: public ApiHooker {

public:
	VoidApiHooker();
	virtual ~VoidApiHooker();
	bool parseParameter();
	bool simpleProcess();
};

#endif /* VOIDAPIHOOKER_H_ */
