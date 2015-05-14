/*
 * CollectedApiInfo.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "CollectedApiInfo.h"

CollectedApiInfo::CollectedApiInfo() {
	// TODO Auto-generated constructor stub
	setTime();
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
	unsigned long int tid = pthread_self();
	return (int) tid;
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

	root["number"] = 0;
	root["name"] = this->mClassName + "." +this->mMethodName;
	root["time"] = this->mTime;
	root["threadID"] = 0;
	root["设备标识码"] = "0000暂无";
	root["应用版本标识码"] = "0000暂无";

	string out = root.toStyledString();
	LOGD("CollectedApiInfo类正在转换json，输出为%s", out.data());
	return out;
}
//private
bool CollectedApiInfo::setTime() {
	long timeNow = time(NULL);
	struct tm* p = localtime(&timeNow);
	stringstream ss;
	ss << p->tm_year + 1900 << "-" << p->tm_mon + 1 << "-" << p->tm_mday << " "
			<< p->tm_hour << ":" << p->tm_min << ":" << p->tm_sec ;
	this->mTime = ss.str();
	return true;
}
