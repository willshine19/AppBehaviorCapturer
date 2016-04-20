/*
 * CollectedApiInfo.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "CollectedApiInfo.h"

CollectedApiInfo::CollectedApiInfo() {
	// TODO Auto-generated constructor stub
	mClassName = "";
	mMethodName = "";
	mTime = "";
	json2string = "";
	mContext = "";
	mParameter = "";
	mResult = "";
	mFatherThreadId = 0;
	mThreadId = 0;
	mProcessID = 0;
	mSonThreadId = 0;
	mResult = "";
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
//zds
string CollectedApiInfo::getContext() {
	return this->mContext;
}
bool CollectedApiInfo::setContext(string Context) {
	this->mContext = Context;
	return true;
}
long CollectedApiInfo::getFatherThreadId() {
	return this->mFatherThreadId;
}
bool CollectedApiInfo::setFatherThreadId(long FatherThreadId) {
	this->mFatherThreadId = FatherThreadId;
	return true;
}
long CollectedApiInfo::getSonThreadId() {
	return this->mSonThreadId;
}
bool CollectedApiInfo::setSonThreadId(long SonThreadId) {
	this->mSonThreadId = SonThreadId;
	return true;
}
//end
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

string CollectedApiInfo::convertToJson() {
	Json::Value root;
	LOGE("11111111111111CollectedApiInfo json start 输出为%s", this->mMethodName.c_str());
	root["number"] = this->mNumber;
	root["name"] = this->mClassName + "." + this->mMethodName;
	root["time"] = this->mTime;
	root["context"] = this->mContext; //zds add
	root["FatherThreadId"] = (unsigned int) this->mFatherThreadId; //zds add
	root["SonThreadId"] = (unsigned int) this->mSonThreadId; //zds add
	root["threadID"] = (unsigned int) this->mThreadId;
	root["processID"] = this->mProcessID;
	root["result"] = this->mResult;
	LOGE("11111111111111CollectedApiInfo json end 输出为%s", this->mMethodName.c_str());

//	json2string = root.toStyledString();
	string out = root.toStyledString();
	LOGE("11111111111111CollectedApiInfo json tostring 输出为%s", out.c_str());
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
			<< p->tm_hour << ":" << p->tm_min << ":" << p->tm_sec << ":"
			<< tv.tv_usec / 1000 << ":" << tv.tv_usec % 1000;
	this->mTime = ss.str();
	return true;
}
