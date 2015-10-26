/*
 * DisableBluetoothAdapter.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "DisableBluetoothAdapter.h"

DisableBluetoothAdapter::DisableBluetoothAdapter() {
	this->mApiDeclaration = *(new ApiDeclaration("android/bluetooth/BluetoothAdapter",
			"disable", "()Z", false, NULL, NULL, NULL));

}

DisableBluetoothAdapter::~DisableBluetoothAdapter() {
	// TODO Auto-generated destructor stub
}

