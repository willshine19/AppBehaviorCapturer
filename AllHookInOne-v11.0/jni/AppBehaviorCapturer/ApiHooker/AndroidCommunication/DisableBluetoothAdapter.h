/*
 * DisableBluetoothAdapter.h
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#ifndef DISABLEBLUETOOTHADAPTER_H_
#define DISABLEBLUETOOTHADAPTER_H_

#include "../ApiHooker.h"

/*
 *
 */
class DisableBluetoothAdapter: public ApiHooker {
public:
	DisableBluetoothAdapter();
	~DisableBluetoothAdapter();
	bool parseResult(Object* obj);
};

#endif /* DISABLEBLUETOOTHADAPTER_H_ */
