/*
 * VoidApiHooker.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "VoidApiHooker.h"
//#include "../System/ApiHookerManager.h"//zds add

VoidApiHooker::VoidApiHooker() {
	// TODO Auto-generated constructor stub

}

VoidApiHooker::~VoidApiHooker() {
	// TODO Auto-generated destructor stub
}

//实现ParseParameter,simpleProcess函数
bool VoidApiHooker::parseParameter(const u4* args){
	return true;
}
bool VoidApiHooker::simpleProcess(){
	return true;
}
