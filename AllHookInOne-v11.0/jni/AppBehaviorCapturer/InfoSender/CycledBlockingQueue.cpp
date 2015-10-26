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
	LOGD("[队列]写指针 is %d, 读指针 is %d, 队列总容量 is %d", writePointer, readPointer, capacity);
	if (((writePointer + 1) & (this->capacity - 1)) == readPointer) { //is full?
		LOGD("[CycedBlockingQueue] Get now available position failed!!!");
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
unsigned int CycledBlockingQueue::getQueueCapacity(){
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
	pthread_mutex_lock(&(queue[readPointer].mutex));
	int read_point = readPointer;
	readPointer = (readPointer + 1) & (capacity - 1);
	return queue[read_point].mCollectedApiInfo;
}
