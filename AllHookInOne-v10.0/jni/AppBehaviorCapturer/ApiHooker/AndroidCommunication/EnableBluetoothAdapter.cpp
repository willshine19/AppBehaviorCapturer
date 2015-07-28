/*
 * EnableBluetoothAdapter.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "EnableBluetoothAdapter.h"

EnableBluetoothAdapter::EnableBluetoothAdapter() {
	this->mApiDeclaration = *(new ApiDeclaration("android/bluetooth/BluetoothAdapter",
				"enable","()Z",false,NULL,NULL,NULL));

}

EnableBluetoothAdapter::~EnableBluetoothAdapter() {
	// TODO Auto-generated destructor stub
}

