/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "getBaseStationIdApiHooker.h"

getBaseStationIdApiHooker::getBaseStationIdApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/telephony/cdma/CdmaCellLocation",
			"getBaseStationId","()I",false,NULL,NULL,NULL));
}

getBaseStationIdApiHooker::~getBaseStationIdApiHooker() {
	// TODO Auto-generated destructor stub
}

