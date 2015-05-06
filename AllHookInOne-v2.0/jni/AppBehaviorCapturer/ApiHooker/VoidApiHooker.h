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
	VoidApiHooker(ApiDeclaration* methodDeclaration,CollectedApiInfo* collectedApiInfo);
	virtual ~VoidApiHooker();

	bool ParseParameter();
	bool SimpleProcess();
};

#endif /* VOIDAPIHOOKER_H_ */
