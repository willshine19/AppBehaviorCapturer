/*
 * Bucket.h
 *
 *  Created on: May 22, 2015
 *      Author: sr
 */

#ifndef BUCKET_H_
#define BUCKET_H_
#include <pthread.h>
#include <string>
#include "../ApiInfo/CollectedApiInfo.h"
class Bucket {
public:
	Bucket();
	virtual ~Bucket();

	CollectedApiInfo mCollectedApiInfo;
	pthread_mutex_t bucketMutex;

	// 向mCollectedApiInfo中写
	bool setClassName(string className);
	bool setMethodName(string methodName);
	bool setThreadId(long threadId);
	bool setTime();
	bool setContext(string context);
	bool setFatherThreadId(long FatherThreadId);

	bool setSonThreadId(long SonThreadId);
	long getSonThreadId();

	// 从mCollectedApiInfo中读
	string getClassName();
	string getMethodName();
	string getTime();
	string getContext();
	long getFatherThreadId();
	unsigned int getThreadId();

};

#endif /* BUCKET_H_ */
