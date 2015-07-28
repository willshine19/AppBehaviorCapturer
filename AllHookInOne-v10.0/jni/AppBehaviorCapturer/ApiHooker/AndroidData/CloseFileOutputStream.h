/*
 * CloseFileOutputStream.h
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#ifndef CLOSEFILEOUTPUTSTREAM_H_
#define CLOSEFILEOUTPUTSTREAM_H_

#include "../VoidApiHooker.h"

/*
 *
 */
class CloseFileOutputStream: public VoidApiHooker {
public:
	CloseFileOutputStream();
	~CloseFileOutputStream();
};

#endif /* CLOSEFILEOUTPUTSTREAM_H_ */
