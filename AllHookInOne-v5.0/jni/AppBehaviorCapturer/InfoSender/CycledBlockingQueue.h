/*
 * CycledBlockingQueue.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef CYCLEDBLOCKINGQUEUE_H_
#define CYCLEDBLOCKINGQUEUE_H_

#include "BlockingQueue.h"
#include "Bucket.h"
#include <pthread.h>
class CycledBlockingQueue: public BlockingQueue {
public:
	CycledBlockingQueue();
	CycledBlockingQueue(int c);
	virtual ~CycledBlockingQueue();
	int getNowAvailablePosition();
	bool push(CollectedApiInfo apiInfo);
	//实现BlockingQueue的send方法
	bool send();
private:
	unsigned int capacity;
	Bucket* queue;
	unsigned int wp;
	unsigned int rp;
	pthread_mutex_t queue_write_mutex;
};

#endif /* CYCLEDBLOCKINGQUEUE_H_ */
