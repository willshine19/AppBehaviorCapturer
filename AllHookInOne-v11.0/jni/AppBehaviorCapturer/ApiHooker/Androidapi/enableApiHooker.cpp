/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "enableApiHooker.h"

enableApiHooker::enableApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/bluetooth/BluetoothAdapter",
			"enable","()Z",false,NULL,NULL,NULL));
}

enableApiHooker::~enableApiHooker() {
	// TODO Auto-generated destructor stub
}

