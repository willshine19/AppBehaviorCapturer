/*
 * CollectedApiInfo.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "CollectedApiInfo.h"

CollectedApiInfo::CollectedApiInfo() {
	// TODO Auto-generated constructor stub
	mNumber = 0;
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

int CollectedApiInfo::getThreadId() {
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

bool CollectedApiInfo::setThreadId(u4 threadId) {
	this->mThreadId = threadId;
	return true;
}
string CollectedApiInfo::convertToJson()
{
	Json::Value root;

	root["number"] = ++mNumber;
	root["name"] = this->mClassName + "." +this->mMethodName;
	root["time"] = this->mTime;
	root["threadID"] = this->mThreadId;

	string out = root.toStyledString();
	LOGD("CollectedApiInfo类正在转换json，输出为%s", out.data());
	return out;
}
//private
bool CollectedApiInfo::setTime() {
	long timeNow = time(NULL);
	struct tm* p = localtime(&timeNow);
	// 获取毫秒和微秒
	struct timeval tv;
	gettimeofday(&tv, NULL);
	//cout << "毫秒：" << tv.tv_usec / 1000 ;
	//cout << "微秒：" << tv.tv_usec % 1000 << endl;
	stringstream ss;
	ss << p->tm_year + 1900 << "-" << p->tm_mon + 1 << "-" << p->tm_mday << " "
			<< p->tm_hour << ":" << p->tm_min << ":" << p->tm_sec  << ":" << tv.tv_usec / 1000 <<":" << tv.tv_usec % 1000 ;
	this->mTime = ss.str();
	return true;
}
