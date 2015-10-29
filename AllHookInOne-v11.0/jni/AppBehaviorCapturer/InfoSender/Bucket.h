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

	// 向mCollectedApiInfo中写
	bool setClassName(string className);
	bool setMethodName(string methodName);
	bool setThreadId(long threadId);
	bool setTime();
	bool setContext(string context);

	// 从mCollectedApiInfo中读
	string getClassName();
	string getMethodName();
	string getTime();
	string getContext();
	unsigned int getThreadId();

	CollectedApiInfo mCollectedApiInfo;
	pthread_mutex_t mutex;
};

#endif /* BUCKET_H_ */
