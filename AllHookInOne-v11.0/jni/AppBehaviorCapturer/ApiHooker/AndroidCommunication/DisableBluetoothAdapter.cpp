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

bool DisableBluetoothAdapter::parseResult(Object* obj) {
	const char* className = "java/lang/Boolean";
	char* resultString = parseObjectToString(obj, className);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(resultString);
	return true;
}
