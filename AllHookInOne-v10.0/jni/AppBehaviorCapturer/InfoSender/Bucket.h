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

	bool setClassName(string ClassName);
	bool setMethodName(string MethodName);
	bool setThreadId(u4 ThreadId);
	bool setTime();

	string getClassName();
	string getMethodName();
	string getTime();
	unsigned int getThreadId();

	CollectedApiInfo m;
	pthread_mutex_t bucket_read_mutex;
};

#endif /* BUCKET_H_ */
