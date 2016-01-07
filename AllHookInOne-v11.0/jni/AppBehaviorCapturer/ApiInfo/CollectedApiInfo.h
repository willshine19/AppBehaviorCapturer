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
#include <sys/time.h>
#include <sstream>
#include <pthread.h>
#include <unistd.h>
#include "object.h"
#include "common.h"
#include "../Utils/json/json/json.h"

using namespace std;

class CollectedApiInfo {
	string mClassName;
	string mMethodName;
	string mTime;
	string json2string;
	string mContext;
	char* mParameter;
	char* mResult;
	long mFatherThreadId;
	long mThreadId;
	int mProcessID;
	long mSonThreadId;
//	char args[10];
//	int flag;
//	pthread_mutex_t lock;
	int mNumber; //序号
public:
	CollectedApiInfo();
	virtual ~CollectedApiInfo();
	string getClassName();
	string getMethodName();
	string getTime();
	long getThreadId();
	int getFlag();
	string getContext();
	long getFatherThreadId();

	long getSonThreadId();
	bool setSonThreadId(long SonThreadId);

	pthread_mutex_t getLock();
	//改成私有成员函数
	bool setClassName(string ClasName);
	bool setMethodName(string MethodName);
	bool setThreadId(long ThreadId);
	bool setContext(string Context);
	bool setFatherThreadId(long FatherThreadId);
	bool setTime();
	bool setFlag(int flag);
	bool setLock(pthread_mutex_t lock);
	string convertToJson();

	char* getParameter() const {
		return mParameter;
	}

	void setParameter(char* parameter) {
		mParameter = parameter;
	}

	char* getResult() const {
		return mResult;
	}

	void setResult(char* result) {
		mResult = result;
	}


};

#endif /* COLLECTEDAPIINFO_H_ */
