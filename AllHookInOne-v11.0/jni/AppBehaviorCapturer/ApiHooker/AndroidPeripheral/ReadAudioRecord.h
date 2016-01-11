/*
 * ReadAudioRecord.h
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#ifndef READAUDIORECORD_H_
#define READAUDIORECORD_H_

#include "../ApiHooker.h"

/*
 *
 */
class ReadAudioRecord: public ApiHooker {
public:
	ReadAudioRecord();
	~ReadAudioRecord();
	bool parseResult(Object* obj);
};

#endif /* READAUDIORECORD_H_ */
