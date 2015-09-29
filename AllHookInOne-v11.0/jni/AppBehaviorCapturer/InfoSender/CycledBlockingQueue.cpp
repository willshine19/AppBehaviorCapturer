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
	// TODO Auto-generated constructor stub
	LOGD("construct CyledBlockingQueue success");
	this->capacity = 10;
	queue = new Bucket[capacity];
	wp = 0;
	rp = 0;
	pthread_mutex_init(&queue_write_mutex, NULL);
}

/**
 * 含参构造函数
 * @param c: Bucket数组的容量
 */
CycledBlockingQueue::CycledBlockingQueue(int c) {
	this->capacity = c;
	queue = new Bucket[c];
	wp = 0;
	rp = 0;
	pthread_mutex_init(&queue_write_mutex, NULL);
}

/**
 * 析构函数
 */
CycledBlockingQueue::~CycledBlockingQueue() {
	// TODO Auto-generated destructor stub
	this->capacity = 0;
	delete[] queue;
	wp = 0;
	rp = 0;
	pthread_mutex_destroy(&queue_write_mutex);
}

/**
 * 返回可写的位置
 * @return:
 */
int CycledBlockingQueue::getNowAvailablePosition() {
	pthread_mutex_lock(&queue_write_mutex);
	LOGD("wp is %d,rp is %d,capacity is %d",wp,rp,capacity);
	if (((wp + 1) & (this->capacity - 1)) == rp) { //is full?
		LOGD("[CycedBlockingQueue] Get now available position failed!!!");
		return -1;
	}
	int ret = wp;
	wp = (wp + 1) & (capacity - 1);
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
	// TODO Auto-generated destructor stub
	pthread_mutex_lock(&(queue[rp].bucket_read_mutex));
	int read_point = rp;
	char* ret;
/*	LOGD("ReadingThread-------------------------position =  %d",rp);
	LOGD("ReadingThread-------------------------className is %s",queue[rp].getClassName().data());
	LOGD("ReadingThread-------------------------methodName is %s",queue[rp].getMethodName().data());
	LOGD("ReadingThread-------------------------threadID is %ud",queue[rp].getThreadId());*/
	rp = (rp + 1) & (capacity - 1);
	return queue[read_point].m;
//	return true;
}
