/*
 * ApiHooker.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "ApiHooker.h"

ApiHooker::ApiHooker() {
	// TODO Auto-generated constructor stub
}
ApiHooker::~ApiHooker() {
	// TODO Auto-generated destructor stub
}
ApiDeclaration ApiHooker::getApiDeclaration(){
	return this->mApiDeclaration;
}
int ApiHooker::getApiFlag(){
	return this->mFlag;
}
string ApiHooker::toString()
{
	return mApiDeclaration.getClassName() + " "
			+  mApiDeclaration.getApiName()+ " "
			+ mApiDeclaration.getApiName();
}
bool ApiHooker::collectBaseInfo(unsigned int threadID)
{
	this->mCollectedApiInfo.setClassName(this->mApiDeclaration.getClassName());
	this->mCollectedApiInfo.setMethodName(this->mApiDeclaration.getApiName());
	this->mCollectedApiInfo.setThreadId(threadID);
	this->mCollectedApiInfo.setTime();
	LOGD( "mCollectedApiInfo ClassName: %s", this->mCollectedApiInfo.getClassName().data() );
	LOGD( "mCollectedApiInfo MethodName: %s", this->mCollectedApiInfo.getMethodName().data() );
	LOGD( "mCollectedApiInfo Time: %s", this->mCollectedApiInfo.getTime().data());
	LOGD("mCollectedApiInfo ThreadID: %d", this->mCollectedApiInfo.getThreadId() );
	this->mCollectedApiInfo.convertToJson();
	return true;
}
bool ApiHooker::saveToQueue(){
	LOGD("saveToQueue method has been called successfully in ApiHooker");
	return true;
}
//模板方法，
bool ApiHooker::main(unsigned int threadID){
	collectBaseInfo(threadID);
	saveToQueue();
	parseParameter();
	simpleProcess();
	return true;
}
