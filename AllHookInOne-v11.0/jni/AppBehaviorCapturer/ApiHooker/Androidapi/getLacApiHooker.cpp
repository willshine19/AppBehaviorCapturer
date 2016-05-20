/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getLacApiHooker.h"

getLacApiHooker::getLacApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/gsm/GsmCellLocation",
			"getLac","()I",false,NULL,NULL,NULL));
}

getLacApiHooker::~getLacApiHooker() {
	// TODO Auto-generated destructor stub
}

