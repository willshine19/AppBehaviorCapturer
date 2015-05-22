/*
 * CycledBlockingQueue.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */
#include <iostream>
#include "CycledBlockingQueue.h"
using namespace std;

CycledBlockingQueue::CycledBlockingQueue() {
	// TODO Auto-generated constructor stub
	cout << "construce CyledBlockingQueue success" << endl;
	this->capacity = 10;
	queue = new Bucket[capacity];
	wp = 0;
	rp = 0;
	pthread_mutex_init(&queue_write_mutex, NULL);
}
CycledBlockingQueue::CycledBlockingQueue(int c) {
	this->capacity = c;
	queue = new Bucket[c];
	wp = 0;
	rp = 0;
	pthread_mutex_init(&queue_write_mutex, NULL);

}
CycledBlockingQueue::~CycledBlockingQueue() {
	// TODO Auto-generated destructor stub
	this->capacity = 0;
	delete[] queue;
	wp = 0;
	rp = 0;
	pthread_mutex_destroy(&queue_write_mutex);
}
int CycledBlockingQueue::getNowAvailablePosition() {
	pthread_mutex_lock(&queue_write_mutex);
	if (((wp + 1) & (capacity - 1)) == rp) { //is full?
		cout << "[CycedBlockingQueue] Get now available position failed!!!"
				<< endl;
		return -1;
	}
	int ret = wp;
	wp = (wp + 1) & (capacity - 1);
	pthread_mutex_unlock(&queue_write_mutex);
	return ret;
}
bool CycledBlockingQueue::push(CollectedApiInfo apiInfo) {
	return false;

}
bool CycledBlockingQueue::send() {
	// TODO Auto-generated destructor stub
	pthread_mutex_lock(&(queue[rp].bucket_read_mutex));
	char* ret;

	{
		cout << "position = " << rp <<endl;
		cout << "taken ClassName" << queue[rp].getClassName() << endl;
		cout << "taken MethodName" << queue[rp].getMethodName() << endl;
		cout << "taken ThreadId" << queue[rp].getThreadId() << endl;
		rp = (rp + 1) & (capacity - 1);

		return true;
	}

}
