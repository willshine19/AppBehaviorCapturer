/*
 * ThreadMap.cpp
 *
 *  Created on: 2015-10-26
 *      Author: zds
 */

#include "ThreadMap.h"

/**
 * 构造函数
 * ThreadMap函数用来存储使用c和java方法获取的线程号
 * 在RunThreadApiHook中被调用
 */
ThreadMap::ThreadMap() {
	pthread_mutex_init(&lock, NULL);
}

ThreadMap::~ThreadMap() {
	// TODO Auto-generated destructor stub
}

//静态成员变量初始化
ThreadMap* ThreadMap::mThreadMap = NULL;
pthread_mutex_t ThreadMap::lock = PTHREAD_MUTEX_INITIALIZER;

ThreadMap* ThreadMap::getInstance() {

	pthread_mutex_lock(&lock);
	if (mThreadMap == NULL) {
		mThreadMap = new ThreadMap();
	}
	pthread_mutex_unlock(&lock);
	return mThreadMap;
}

