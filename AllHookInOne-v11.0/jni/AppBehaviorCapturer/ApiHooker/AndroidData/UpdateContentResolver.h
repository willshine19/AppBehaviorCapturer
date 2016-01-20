/*
 * UpdateContentResolver.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef UPDATECONTENTRESOLVER_H_
#define UPDATECONTENTRESOLVER_H_

#include "../ApiHooker.h"

/*
 *
 */
class UpdateContentResolver: public ApiHooker {
public:
	UpdateContentResolver();
	~UpdateContentResolver();
	bool parseResult(Object* obj);
};

#endif /* UPDATECONTENTRESOLVER_H_ */
