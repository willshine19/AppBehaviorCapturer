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
 * result的存储在每个apihook中
 */bool ApiHooker::collectBaseInfo() {
	long threadId = pthread_self();
	if (threadId == 0) {
		LOGE("getThreadID falied");
	}
//	pthread_mutex_t* mutex =
//			&(InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].bucketMutex);
//	pthread_mutex_lock(mutex); 不注释会死锁
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setClassName(
			this->mApiDeclaration.getClassName());
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setMethodName(
			this->mApiDeclaration.getApiName());
//	LOGE("11111111apihooker:%s", this->mApiDeclaration.getApiName().c_str());
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setTime();
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setThreadId(
			threadId);
	//zds add
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setContext(
			ApiHookerManager::getInstance()->mContextInfo);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setFatherThreadId(
			getFatherId(threadId)); //
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setSonThreadId(
			getSonId(threadId)); //
	pthread_mutex_t* mutex =
			&(InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].bucketMutex);
	pthread_mutex_unlock(mutex);
	return true;
}

long ApiHooker::getFatherId(long threadId) {
//	long threadId = pthread_self();
	auto mMapFound = (ThreadMap::getInstance()->mpid_father_son_Map).find(
			threadId);
	if (mMapFound != (ThreadMap::getInstance()->mpid_father_son_Map).end()) {
		return mMapFound->second;
	} else
//		LOGD("This thread don't have a father thread");
		return 0;
}
long ApiHooker::getSonId(long threadId) {
//	long threadId = pthread_self();
	auto mMapFound = (ThreadMap::getInstance()->mpid_javason_father_Map).find(
			threadId);
	if (mMapFound
			!= (ThreadMap::getInstance()->mpid_javason_father_Map).end()) {
		return mMapFound->second;
	} else
//		LOGD("This thread don't have a father thread");
		return 0;
}

/**
 * 空函数
 */bool ApiHooker::saveToQueue() {
	LOGD("saveToQueue method has been called successfully in ApiHooker");
	return true;
}

/**
 * ApiHooker类的入口
 * 在DalvikMethodHooker.cpp 中的methodHandler()函数中被调用
 */bool ApiHooker::main(const u4* args) {
	pthread_mutex_lock(&lock);
	//申请队列空闲位置
	this->mQueuePosition =
			InfoSender::mCycledBlockingQueue->getNowAvailablePosition();
	if (mQueuePosition == -1)
		return false;
	parseParameter(args);
//	collectBaseInfo();
//	saveToQueue();
	pthread_mutex_unlock(&lock);
	return true;
}

/**
 * object返回值解析
 * 该函数可以解析一个Object对象,该Object对象代表一个java层的java对象,调用这个java对象的toString方法
 * 参数:obj 解析目标; className 字符串,表示对应的java对象的名字,比如java/io/FileDescriptor
 * 返回:字符串 返回该java对象的toString方法的返回值
 */
char* ApiHooker::parseObjectToString(Object* obj, const char* className) {
	// 调用该对象的toString方法
	// 参数1 obj
	// 参数2 method_this
	JNIEnv *env = AndroidRuntime::getJNIEnv();
	jclass longclass = env->FindClass(className);
	if (longclass == 0) {
		LOGE("Get Class failed");
	}
	jmethodID methodID = env->GetMethodID(longclass, "toString",
			"()Ljava/lang/String;");
	if (methodID == 0) {
		LOGE("get method failed");
	}
	Method* method_this = (Method*) methodID;
	// 参数3 argList
	u4* uriArgs = (u4*) 1;
	ArrayObject* argList = dvmBoxMethodArgs(method_this, uriArgs);
	// 参数4 params
	ArrayObject* params = (ArrayObject *) dvmGetMethodParamTypes(method_this,
			"()Ljava/lang/String;");
	// 参数5 returnType
	ClassObject* returnType = (ClassObject *) dvmGetBoxedReturnType(
			method_this);

	// 调用toString方法
	Object* stringResult = dvmInvokeMethod(obj, method_this, argList, params,
			returnType, true);

	StringObject* stringObjId = (StringObject*) stringResult;
	char* resultString = dvmCreateCstrFromString(stringObjId);
	return resultString;
}
