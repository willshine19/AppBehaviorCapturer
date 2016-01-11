/*
 * OpenCamera.h
 *
 *  Created on: 2015-6-17
 *      Author: sang
 */

#ifndef OPENCAMERA_H_
#define OPENCAMERA_H_

#include "../ApiHooker.h"

/*
 *
 */
class OpenCamera: public ApiHooker {
public:
	OpenCamera();
	~OpenCamera();
	bool parseResult(Object* obj);
};

#endif /* OPENCAMERA_H_ */
