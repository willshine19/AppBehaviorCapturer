/*
 * GetLastKnownLocationApiHooker.cpp
 *
 *  Created on: 2015-5-27
 *      Author: long
 */

#include "GetLastKnownLocationApiHooker.h"

GetLastKnownLocationApiHooker::GetLastKnownLocationApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/location/LocationManager",
			"getLastKnownLocation","(Ljava/lang/String;)Landroid/location/Location;",false,NULL,NULL,NULL));

}

GetLastKnownLocationApiHooker::~GetLastKnownLocationApiHooker() {
	// TODO Auto-generated destructor stub
}

