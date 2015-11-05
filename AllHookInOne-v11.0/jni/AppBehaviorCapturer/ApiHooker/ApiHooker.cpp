/*
 * ApiHooker.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "ApiHooker.h"
#include "../System/ApiHookerManager.h"//zds add
/**
 * 构造函数
 */
ApiHooker::ApiHooker() {
	pthread_mutex_init(&lock, NULL);
}

ApiHooker::~ApiHooker() {
	// TODO Auto-generated destructor stub
}

ApiDeclaration ApiHooker::getApiDeclaration() {
	return this->mApiDeclaration;
}

string ApiHooker::toString() {
	return mApiDeclaration.getClassName() + " " + mApiDeclaration.getApiName()
			+ " " + mApiDeclaration.getApiName();
}

/**
 * 将类名 方法名 时间 线程号 存入循环队列的Bucket实例中
 */
bool ApiHooker::collectBaseInfo() {
	long threadId = pthread_self();
//	LOGD("ThreadID is  %ld", threadId);
	if (threadId == 0) {
		LOGE("getThreadID falied");
	}
	pthread_mutex_t* mutex =
			&(InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].mutex);
//	pthread_mutex_lock(mutex); 不注释会死锁
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setClassName(
			this->mApiDeclaration.getClassName());
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setMethodName(
			this->mApiDeclaration.getApiName());
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setTime();
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setThreadId(
			threadId);
	//zds add
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setContext(
			ApiHookerManager::getInstance()->mcontextinfo);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setFatherThreadId(
			GetFatherId());
	LOGD("[+] apihooker-Infosender的context数据为 %s",
			(ApiHookerManager::getInstance()->mcontextinfo).c_str());
	LOGD("[+] apihooker-Infosender的fatherid数据为 %ld", GetFatherId());
	//end
	pthread_mutex_unlock(mutex);
	return true;
}

long ApiHooker::GetFatherId() {
	long threadId = pthread_self();
	auto mMapFound = (ThreadMap::getInstance()->mpid_father_son_Map).find(
			threadId);
	if (mMapFound != (ThreadMap::getInstance()->mpid_father_son_Map).end()) {
		return mMapFound->second;
	} else
		LOGD("This thread don't have a father thread");
	return 0;
}

bool ApiHooker::saveToQueue() {
	LOGD("saveToQueue method has been called successfully in ApiHooker");
	return true;
}

/**
 * ApiHooker类的入口
 * 在DalvikMethodHooker.cpp 中的methodHandler()函数中被调用
 */
bool ApiHooker::main(const u4* args) {
	pthread_mutex_lock(&lock);
	//申请队列空闲位置
	this->mQueuePosition =
			InfoSender::mCycledBlockingQueue->getNowAvailablePosition();
	parseParameter(args);
	collectBaseInfo();
	saveToQueue();

	simpleProcess();
	pthread_mutex_unlock(&lock);
	return true;
}
