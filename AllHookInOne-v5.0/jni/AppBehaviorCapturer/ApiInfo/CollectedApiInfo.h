/*
 * CollectedApiInfo.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef COLLECTEDAPIINFO_H_
#define COLLECTEDAPIINFO_H_

#include <string>
#include <time.h>
#include <sstream>
#include <pthread.h>
#include "object.h"
#include "common.h"
#include "../Utils/json/json/json.h"

using namespace std;

class CollectedApiInfo {
	string mClassName;
	string mMethodName;
	string mTime;
	unsigned long int mThreadId;
	char args[10];
	int flag;
	pthread_mutex_t lock;
public:
	CollectedApiInfo();
	virtual ~CollectedApiInfo();
	string getClassName();
	string getMethodName();
	string getTime();
	int getThreadId();
	int getFlag();
	pthread_mutex_t getLock();
	//改成私有成员函数
	bool setClassName(string ClasName);
	bool setMethodName(string MethodName);
	bool setThreadId(u4 ThreadId);
	bool setFlag(int flag);
	bool setLock(pthread_mutex_t lock);
	string convertToJson();

private:
	bool setTime();
};

#endif /* COLLECTEDAPIINFO_H_ */
