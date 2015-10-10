/*
 * CollectedApiInfo.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "CollectedApiInfo.h"

CollectedApiInfo::CollectedApiInfo() {
	// TODO Auto-generated constructor stub
	mProcessID = getpid();

}

CollectedApiInfo::~CollectedApiInfo() {
	// TODO Auto-generated destructor stub
}

//collectedApiInfo get/set method
string CollectedApiInfo::getClassName() {
	return this->mClassName;
}

string CollectedApiInfo::getMethodName() {
	return this->mMethodName;
}

string CollectedApiInfo::getTime() {
	return this->mTime;
}
long CollectedApiInfo::getThreadId() {
//	long tid = pthread_self();
	return this->mThreadId;
}

bool CollectedApiInfo::setClassName(string className) {
	this->mClassName = className;
	return true;
}

bool CollectedApiInfo::setMethodName(string methodName) {
	this->mMethodName = methodName;
	return true;
}

bool CollectedApiInfo::setThreadId(long threadId) {
	this->mThreadId = threadId;
	return true;
}
string CollectedApiInfo::convertToJson()
{
	Json::Value root;

	root["number"] = 0;
	root["name"] = this->mClassName + "." +this->mMethodName;
	root["time"] = this->mTime;
	root["threadID"] = (unsigned int)this->mThreadId;
	root["processID"] = this->mProcessID;

//	json2string = root.toStyledString();
	string out = root.toStyledString();
//	const char* out = root.asCString();
//	temp = root.asString();
	LOGD("CollectedApiInfo类正在转换json，输出为%s", out.data());
	return out;
}
// 获得当前时间 精度为微秒，需要time.h文件
bool CollectedApiInfo::setTime() {
	// 获取时间
	long timeNow = time(NULL);
	struct tm* p = localtime(&timeNow);
	// 获取毫秒和微秒
	struct timeval tv;
	gettimeofday(&tv, NULL);

	stringstream ss;
	ss << p->tm_year + 1900 << "-" << p->tm_mon + 1 << "-" << p->tm_mday << " "
			<< p->tm_hour << ":" << p->tm_min << ":" << p->tm_sec  << ":" << tv.tv_usec / 1000 <<":" << tv.tv_usec % 1000 ;
	this->mTime = ss.str();
	return true;
}