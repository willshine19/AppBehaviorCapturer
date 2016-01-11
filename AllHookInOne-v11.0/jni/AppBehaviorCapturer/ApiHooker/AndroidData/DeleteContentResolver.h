/*
 * DeleteContentResolver.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef DELETECONTENTRESOLVER_H_
#define DELETECONTENTRESOLVER_H_

#include "../ApiHooker.h"

/*
 *
 */
class DeleteContentResolver: public ApiHooker {
public:
	DeleteContentResolver();
	~DeleteContentResolver();
	bool parseResult(Object* obj);
};

#endif /* DELETECONTENTRESOLVER_H_ */
