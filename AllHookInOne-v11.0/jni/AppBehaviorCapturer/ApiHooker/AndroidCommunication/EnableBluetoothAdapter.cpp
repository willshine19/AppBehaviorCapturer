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

bool EnableBluetoothAdapter::parseResult(Object* obj) {
	const char* className = "java/lang/Boolean";
	char* resultString = parseObjectToString(obj, className);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(resultString);
	return true;
}
