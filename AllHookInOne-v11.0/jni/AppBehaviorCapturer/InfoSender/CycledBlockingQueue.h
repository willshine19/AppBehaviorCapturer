/*
 * CycledBlockingQueue.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef CYCLEDBLOCKINGQUEUE_H_
#define CYCLEDBLOCKINGQUEUE_H_

#include "common.h"
#include "BlockingQueue.h"
#include "Bucket.h"
#include <pthread.h>
class CycledBlockingQueue: public BlockingQueue {
public:
	Bucket* queue;
	CycledBlockingQueue();
	CycledBlockingQueue(int c);
	virtual ~CycledBlockingQueue();
	int getNowAvailablePosition();
	bool push(CollectedApiInfo apiInfo);
	unsigned int getQueueCapacity();
	//实现BlockingQueue的send方法
	CollectedApiInfo send();
private:
	unsigned int capacity;
//	Bucket* queue;
	unsigned int wp; // 写位置
	unsigned int rp; // 读位置
	pthread_mutex_t queue_write_mutex;
};

#endif /* CYCLEDBLOCKINGQUEUE_H_ */
