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

ApiHooker::ApiHooker(ApiDeclaration* apiDeclaration,CollectedApiInfo* collectedApiInfo) {
	this->mApiDeclaration = *apiDeclaration;
	this->mCollectedApiInfo = *collectedApiInfo;
}
ApiHooker::~ApiHooker() {
	// TODO Auto-generated destructor stub
}
ApiDeclaration ApiHooker::getApiDeclaration(){
	return this->mApiDeclaration;
}
/*string ApiHooker::toString()
{
	return mApiDeclaration.getClassName() + " "
			+  mApiDeclaration.getApiName()+ " "
			+ mApiDeclaration.getApiName();
}*/
bool ApiHooker::collectBaseInfo(){
	return true;
}
bool ApiHooker::saveToQueue(){
	return true;
}
//模板方法，
bool ApiHooker::methodHandler(){
	collectBaseInfo();
	saveToQueue();
	parseParameter();
	simpleProcess();
	return true;
}
