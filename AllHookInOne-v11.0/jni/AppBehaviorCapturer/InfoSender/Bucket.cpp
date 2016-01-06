/*
 * Bucket.cpp
 *
 *  Created on: May 22, 2015
 *      Author: sr
 */

#include "Bucket.h"

Bucket::Bucket() {
	// TODO Auto-generated constructor stub
	mCollectedApiInfo = *(new CollectedApiInfo());
	pthread_mutex_init(&bucketMutex, NULL);
	pthread_mutex_lock(&bucketMutex);
}

Bucket::~Bucket() {
	// TODO Auto-generated destructor stub
//	delete m;
	pthread_mutex_destroy(&bucketMutex);
}

bool Bucket::setClassName(string className) {
	this->mCollectedApiInfo.setClassName(className);
	return true;
}
bool Bucket::setMethodName(string methodName) {
	this->mCollectedApiInfo.setMethodName(methodName);
	return true;
}

bool Bucket::setThreadId(long threadId) {
	this->mCollectedApiInfo.setThreadId(threadId);
	return true;
}
bool Bucket::setTime() {
	this->mCollectedApiInfo.setTime();
	return true;
}
//zds
bool Bucket::setContext(string context) {
	this->mCollectedApiInfo.setContext(context);
	return true;
}
string Bucket::getContext() {
	return this->mCollectedApiInfo.getContext();
}
bool Bucket::setFatherThreadId(long FatherThreadId) {
	this->mCollectedApiInfo.setFatherThreadId(FatherThreadId);
	return true;
}
long Bucket::getFatherThreadId() {
	return this->mCollectedApiInfo.getFatherThreadId();
}
bool Bucket::setSonThreadId(long SonThreadId) {
	this->mCollectedApiInfo.setSonThreadId(SonThreadId);
	return true;
}
long Bucket::getSonThreadId() {
	return this->mCollectedApiInfo.getSonThreadId();
}

//end

string Bucket::getClassName() {
	return this->mCollectedApiInfo.getClassName();
}
string Bucket::getMethodName() {
	return this->mCollectedApiInfo.getMethodName();
}
string Bucket::getTime() {
	return this->mCollectedApiInfo.getTime();
}
unsigned int Bucket::getThreadId() {
	return this->mCollectedApiInfo.getThreadId();
}
