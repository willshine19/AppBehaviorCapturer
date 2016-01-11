/*
 * ReadFileInputStream.h
 *
 *  Created on: 2015-6-18
 *      Author: sang
 */

#ifndef READFILEINPUTSTREAM_H_
#define READFILEINPUTSTREAM_H_

#include "../ApiHooker.h"

/*
 *
 */
class ReadFileInputStream: public ApiHooker {
public:
	ReadFileInputStream();
	~ReadFileInputStream();
	bool parseResult(Object* obj);
};

#endif /* READFILEINPUTSTREAM_H_ */
