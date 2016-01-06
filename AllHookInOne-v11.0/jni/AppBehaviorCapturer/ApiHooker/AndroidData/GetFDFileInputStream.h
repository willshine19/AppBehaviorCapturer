/*
 * GetFDFileInputStream.h
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#ifndef GETFDFILEINPUTSTREAM_H_
#define GETFDFILEINPUTSTREAM_H_

#include "../ApiHooker.h"
#include "../../Utils/DalvikMethodHooker.h"
#include "android_runtime/AndroidRuntime.h"
#include "../../System/ApiHookerManager.h"//zds add
/*
 *
 */
class GetFDFileInputStream: public ApiHooker {
public:
	GetFDFileInputStream();
	~GetFDFileInputStream();
	bool parseResult(Object* obj);
};

#endif /* GETFDFILEINPUTSTREAM_H_ */
