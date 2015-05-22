/*
 * BlockingQueue.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef BLOCKINGQUEUE_H_
#define BLOCKINGQUEUE_H_

#include "../ApiInfo/CollectedApiInfo.h"

class BlockingQueue {
public:
	BlockingQueue();
	virtual ~BlockingQueue();

//	bool isFull(BlockingQueue* q);
//	bool isEmpty(BlockingQueue* q);
//	int clear(BlockingQueue* q);
	int push(CollectedApiInfo apiInfo);
	CollectedApiInfo* pull(BlockingQueue* q);
	//虚函数，在CycledBlockingQueue中实现此方法
	virtual bool send(){

		return true;
	}

};

#endif /* BLOCKINGQUEUE_H_ */
