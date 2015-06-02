/*
 * InfoSender.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */
#include <iostream>
#include "InfoSender.h"
using namespace std;

InfoSender::InfoSender(BlockingQueue* blockingQueue) {
	// TODO Auto-generated constructor stub
	cout << "construct InfoSender success " << endl;
//	this->mCycledBlockingQueue = blockingQueue;
	pthread_mutex_init(&InfoSender::lock, NULL);
}

InfoSender::~InfoSender() {
	// TODO Auto-generated destructor stub
}

//静态成员变量初始化
InfoSender* InfoSender::infoSenderInstance = NULL;
CycledBlockingQueue* InfoSender::mCycledBlockingQueue = NULL;
pthread_mutex_t InfoSender::lock = PTHREAD_MUTEX_INITIALIZER;;
//CycledBlockingQueue* mCycledBlockingQueue
//单例模式中访问实例的接口
InfoSender* InfoSender::getInstance(){
	pthread_mutex_lock(&InfoSender::lock);
	if(infoSenderInstance == NULL){
		BlockingQueue *q = new CycledBlockingQueue();
		infoSenderInstance = new InfoSender(q);
	}
	pthread_mutex_unlock(&InfoSender::lock);
	return infoSenderInstance;
}
void* InfoSender::readFromQueue(void* arg){
	LOGD("create reading thread successfully");
	while(1){
		CollectedApiInfo temp = InfoSender::mCycledBlockingQueue->send();
		string s = temp.convertToJson();
	}
	return ((void*)0);
}
int InfoSender::socketConnection(){
	return 1;
}
bool send(){
	return true;
}
//成员函数后面在做补充
bool InfoSender::init(){
	//初始化队列
	InfoSender::mCycledBlockingQueue = new CycledBlockingQueue(1024);
//	this->mCycledBlockingQueue = new CycledBlockingQueue(1024);
	//初始化读线程
	int err = pthread_create(&this->ntid,NULL,InfoSender::readFromQueue,NULL);
	if(err !=0){
		LOGE("can not create thread :%s",strerror(err));
	}
	return true;
}
/*CycledBlockingQueue* InfoSender::getCycledBlockingQueue(){
	return this->mCycledBlockingQueue;
}*/

