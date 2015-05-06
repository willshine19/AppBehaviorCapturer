/*
 * VoidApiHooker.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "VoidApiHooker.h"

VoidApiHooker::VoidApiHooker() {
	// TODO Auto-generated constructor stub

}

VoidApiHooker::VoidApiHooker(ApiDeclaration* apiDeclaration,CollectedApiInfo* collectedApiInfo){
	this->mCollectedApiInfo = *collectedApiInfo;
	this->mApiDeclaration = *apiDeclaration;
}


VoidApiHooker::~VoidApiHooker() {
	// TODO Auto-generated destructor stub
}

//实现ParseParameter,simpleProcess函数
bool VoidApiHooker::ParseParameter(){
	return true;
}
bool VoidApiHooker::SimpleProcess(){
	return true;
}
