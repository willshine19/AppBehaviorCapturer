/*
 * CollectedApiInfo.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef COLLECTEDAPIINFO_H_
#define COLLECTEDAPIINFO_H_

#include <string>
using namespace std;

class CollectedApiInfo {
	string mClassName;
	string mMethodName;
	string mTime;
	int mThreadId;
	char args[10];
	int flag;
	pthread_mutex_t lock;
public:
	CollectedApiInfo();

	virtual ~CollectedApiInfo();

	string getClassName(CollectedApiInfo collectedApiInfo);
	string getMethodName(CollectedApiInfo collectedApiInfo);
	string getTime(CollectedApiInfo collectedApiInfo);
	int getThreadId(CollectedApiInfo collectedApiInfo);

	int getFlag(CollectedApiInfo collectedApiInfo);
	pthread_mutex_t getLock(CollectedApiInfo collectedApiInfo);
//改成私有成员函数
	bool setClassName(CollectedApiInfo collectedApiInfo,string ClasName);
	bool setMethodName(CollectedApiInfo collectedApiInfo,string MethodName);
	bool setTime(CollectedApiInfo collectedApiInfo,string Time);
	bool setThreadId(CollectedApiInfo collectedApiInfo,int ThreadId);

	bool setFlag(CollectedApiInfo collectedApiInfo,int flag);
	bool setLock(CollectedApiInfo collectedApiInfo,pthread_mutex_t lock);

};

#endif /* COLLECTEDAPIINFO_H_ */
