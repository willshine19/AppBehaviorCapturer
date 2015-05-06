/*
 * StartThreadApiHooker.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "StartThreadApiHooker.h"



StartThreadApiHooker::StartThreadApiHooker() {
	// TODO Auto-generated constructor stub

}

StartThreadApiHooker::StartThreadApiHooker(ApiDeclaration* apiDeclaration,CollectedApiInfo* collectedApiInfo){
	this->mCollectedApiInfo = *collectedApiInfo;
	this->mApiDeclaration = *apiDeclaration;
}

StartThreadApiHooker::~StartThreadApiHooker() {
	// TODO Auto-generated destructor stub
}

//实现static methodHandler函数
