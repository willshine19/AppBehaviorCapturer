/*
 * Bucket.cpp
 *
 *  Created on: May 22, 2015
 *      Author: sr
 */

#include "Bucket.h"

Bucket::Bucket() {
	// TODO Auto-generated constructor stub
	m = new CollectedApiInfo;
	pthread_mutex_init(&bucket_read_mutex,NULL);
	pthread_mutex_lock(&bucket_read_mutex);
}

Bucket::~Bucket() {
	// TODO Auto-generated destructor stub
	delete m;
	pthread_mutex_destroy(&bucket_read_mutex);
}

bool Bucket::setClassName(string className){
	this->m->setClassName(className);
	return true;
}
bool Bucket::setMethodName(string methodName) {
	this->m->setMethodName(methodName);
	return true;
}

bool Bucket::setThreadId(u4 threadId) {
	this->m->setThreadId(threadId);
	return true;
}

string Bucket::getClassName(){
	return this->m->getClassName();
}
string Bucket::getMethodName(){
	return this->m->getMethodName();
}
int Bucket::getThreadId(){
	return this->m->getThreadId();
}
