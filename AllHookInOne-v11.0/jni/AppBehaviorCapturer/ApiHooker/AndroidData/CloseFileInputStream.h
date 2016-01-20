/*
 * CloseFileInputStream.h
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#ifndef CLOSEFILEINPUTSTREAM_H_
#define CLOSEFILEINPUTSTREAM_H_

#include "../VoidApiHooker.h"

/*
 *
 */
class CloseFileInputStream: public VoidApiHooker {
public:
	CloseFileInputStream();
	~CloseFileInputStream();

};

#endif /* CLOSEFILEINPUTSTREAM_H_ */
