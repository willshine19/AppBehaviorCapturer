/*
 * DisconnectWifiManager.h
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#ifndef DISCONNECTWIFIMANAGER_H_
#define DISCONNECTWIFIMANAGER_H_

#include "../ApiHooker.h"

/*
 *
 */
class DisconnectWifiManager: public ApiHooker {
public:
	DisconnectWifiManager();
	~DisconnectWifiManager();
};

#endif /* DISCONNECTWIFIMANAGER_H_ */
