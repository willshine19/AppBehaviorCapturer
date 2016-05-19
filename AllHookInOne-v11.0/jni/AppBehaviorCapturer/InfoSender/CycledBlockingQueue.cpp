/*
 * CycledBlockingQueue.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */
#include <iostream>
#include "CycledBlockingQueue.h"
using namespace std;

/**
 * 无参构造函数
 */
CycledBlockingQueue::CycledBlockingQueue() {
	LOGD("construct CyledBlockingQueue success");
	this->capacity = 10;
	queue = new Bucket[capacity];
	writePointer = 0;
	readPointer = 0;
	pthread_mutex_init(&queue_write_mutex, NULL);
}
/**
 * 含参构造函数
 * @param c: Bucket数组的容量
 */
CycledBlockingQueue::CycledBlockingQueue(int capacity) {
	this->capacity = capacity;
	queue = new Bucket[capacity];
	writePointer = 0;
	readPointer = 0;
	pthread_mutex_init(&queue_write_mutex, NULL);
}

/**
 * 析构函数
 */
CycledBlockingQueue::~CycledBlockingQueue() {
	// TODO Auto-generated destructor stub
	this->capacity = 0;
	delete[] queue;
	writePointer = 0;
	readPointer = 0;
	pthread_mutex_destroy(&queue_write_mutex);
}

/**
 * 返回可写的位置
 * @return:
 */
int CycledBlockingQueue::getNowAvailablePosition() {
	pthread_mutex_lock(&queue_write_mutex);
	LOGD(
			"[w][申请队列]写指针 is %d, 读指针 is %d, 队列总容量 is %d", writePointer, readPointer, capacity);
	if (((writePointer + 1) & (this->capacity - 1)) == readPointer) { //is full?
		LOGD("[CycedBlockingQueue] Get now available position failed!!!");
		pthread_mutex_unlock(&queue_write_mutex);
		return -1;
	}
	int ret = writePointer;
	writePointer = (writePointer + 1) & (capacity - 1);
	pthread_mutex_unlock(&queue_write_mutex);
	return ret;
}

/**
 * 返回队列的容量
 * @return: 队列的容量
 */
unsigned int CycledBlockingQueue::getQueueCapacity() {
	return this->capacity;
}

/**
 * push 空
 */
bool CycledBlockingQueue::push(CollectedApiInfo apiInfo) {
	return false;

}

/**
 * 返回队列queue中Bucket实例中的CollectedApiInfo实例
 * 返回：CollectedApiInfo实例
 */
CollectedApiInfo CycledBlockingQueue::send() {

	LOGI("[r]befor lock bucketMutex %d", readPointer);
	int trylock_ret = 0;
	bool suc = false;
	trylock_ret = pthread_mutex_trylock(&(queue[readPointer].bucketMutex));
	if ( trylock_ret == 16){
		suc = true;
		LOGE("[r]trylock_%d ret = %d", readPointer, trylock_ret);
	} else {
		LOGE("[r]trylock_%d ret = %d", readPointer, trylock_ret);
	}

	while (suc) {
//		LOGE("[r]trylock %d busy!!!",readPointer);
		usleep(500);
		int assa = readPointer; //
		for (int i = 0; i < 5; ++i) {
			assa = (readPointer + i) & (capacity - 1);
			//rp+i,i=0,1,2,3,4?
			if (pthread_mutex_trylock(&(queue[assa].bucketMutex)) == 0) {
				LOGE("[r]%d available !!! break !",assa);
				readPointer = assa;
				suc = false;
				break;
			}
		}
	}

	LOGI("[r]after lock bucketMutex %d", readPointer);
	int read_point = readPointer;
	readPointer = (readPointer + 1) & (capacity - 1);
	LOGI(
			"[r]before return, read_point = %d, readPointer = %d", read_point, readPointer);
	return queue[read_point].mCollectedApiInfo;
}
