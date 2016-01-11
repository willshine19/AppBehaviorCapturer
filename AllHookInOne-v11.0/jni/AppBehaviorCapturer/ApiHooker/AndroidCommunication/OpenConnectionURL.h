/*
 * OpenConnectionURL.h
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#ifndef OPENCONNECTIONURL_H_
#define OPENCONNECTIONURL_H_

#include "../ApiHooker.h"

/*
 *
 */
class OpenConnectionURL: public ApiHooker {
public:
	OpenConnectionURL();
	~OpenConnectionURL();
	bool parseResult(Object* obj);
};

#endif /* OPENCONNECTIONURL_H_ */
