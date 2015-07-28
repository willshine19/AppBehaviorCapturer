/*
 * writeFileOutputStreamApiHooker.h
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#ifndef WRITEFILEOUTPUTSTREAMAPIHOOKER_H_
#define WRITEFILEOUTPUTSTREAMAPIHOOKER_H_

#include "../ApiHooker.h"

class WriteFileOutputStreamApiHooker: public ApiHooker {
public:
	WriteFileOutputStreamApiHooker();
	~WriteFileOutputStreamApiHooker();
	bool parseParameter(const u4* args);
};

#endif /* WRITEFILEOUTPUTSTREAMAPIHOOKER_H_ */
