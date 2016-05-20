/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "BigDecimalApiHooker.h"

BigDecimalApiHooker::BigDecimalApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("java/math/BigDecimal",
			"<init>","(I)V",false,NULL,NULL,NULL));
}

BigDecimalApiHooker::~BigDecimalApiHooker() {
	// TODO Auto-generated destructor stub
}

