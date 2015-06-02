/*
 * ApiHooker.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "ApiHooker.h"

ApiHooker::ApiHooker() {
	// TODO Auto-generated constructor stub
	LOGD("construct APiHooker successfully");
	pthread_mutex_init(&lock, NULL);
}
ApiHooker::~ApiHooker() {
	// TODO Auto-generated destructor stub
}
ApiDeclaration ApiHooker::getApiDeclaration(){
	return this->mApiDeclaration;
}

string ApiHooker::toString()
{
	return mApiDeclaration.getClassName() + " "
			+  mApiDeclaration.getApiName()+ " "
			+ mApiDeclaration.getApiName();
}
bool ApiHooker::collectBaseInfo(Thread* self){
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition];
//	InfoSender::getInstance()->getCycledBlockingQueue()->queue[this->mQueuePosition];
	this->mApiDeclaration.getClassName();
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setClassName(this->mApiDeclaration.getClassName());
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setMethodName(this->mApiDeclaration.getApiName());
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setTime();
//	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setThreadId(self->threadId);
	long pid = pthread_self();
//	long pid = InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].getThreadId();
	if(pid==0){
		LOGE("----------------------------------getThreadID falied");
	}
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setThreadId(pid);
/*	LOGD("mCollectedApiInfo ThreadID: %ud",InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].getThreadId());
	LOGD("mCollectedApiInfo Time: %ud",InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].getTime().data());
	LOGD("mCollectedApiInfo ClassName: %s",InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].getClassName().data());
	LOGD("mCollectedApiInfo MethodName: %s", InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].getMethodName().data());*/
	pthread_mutex_unlock(&(InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].bucket_read_mutex));
/*	InfoSender::getInstance()->getCycledBlockingQueue()->queue[this->mQueuePosition].setClassName(this->mApiDeclaration.getClassName());
	InfoSender::getInstance()->getCycledBlockingQueue()->queue[this->mQueuePosition].setMethodName(this->mApiDeclaration.getApiName());
	InfoSender::getInstance()->getCycledBlockingQueue()->queue[this->mQueuePosition].setTime();
	InfoSender::getInstance()->getCycledBlockingQueue()->queue[this->mQueuePosition].setThreadId(self->threadId);
	LOGD("mCollectedApiInfo ThreadID: %ud",InfoSender::getInstance()->getCycledBlockingQueue()->queue[this->mQueuePosition].getThreadId());
	LOGD( "mCollectedApiInfo Time: %s", InfoSender::getInstance()->getCycledBlockingQueue()->queue[this->mQueuePosition].getTime().data() );
	LOGD( "mCollectedApiInfo ClassName: %s", InfoSender::getInstance()->getCycledBlockingQueue()->queue[this->mQueuePosition].getClassName().data() );
	LOGD( "mCollectedApiInfo MethodName: %s", InfoSender::getInstance()->getCycledBlockingQueue()->queue[this->mQueuePosition].getMethodName().data() );*/
	return true;
}
bool ApiHooker::saveToQueue(){
	LOGD("saveToQueue method has been called successfully in ApiHooker");
	return true;
}
//模板方法，
bool ApiHooker::main(Thread* self){
	pthread_mutex_lock(&lock);
	//申请队列空闲位置
	this->mQueuePosition = InfoSender::mCycledBlockingQueue->getNowAvailablePosition();
//	this->mQueuePosition = InfoSender::getInstance()->getCycledBlockingQueue()->getNowAvailablePosition();
	LOGD("get %d available position successfully ",this->mQueuePosition);
	collectBaseInfo(self);
	saveToQueue();
	parseParameter();
	simpleProcess();
	pthread_mutex_unlock(&lock);
	return true;
}
