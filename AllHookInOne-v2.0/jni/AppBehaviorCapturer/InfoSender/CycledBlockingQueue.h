/*
 * CycledBlockingQueue.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef CYCLEDBLOCKINGQUEUE_H_
#define CYCLEDBLOCKINGQUEUE_H_

#include "BlockingQueue.h"

class CycledBlockingQueue: public BlockingQueue {
public:
	CycledBlockingQueue();
	virtual ~CycledBlockingQueue();

	//实现BlockingQueue的send方法
	bool send();
};

#endif /* CYCLEDBLOCKINGQUEUE_H_ */
