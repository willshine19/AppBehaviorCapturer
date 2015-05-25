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

VoidApiHooker::~VoidApiHooker() {
	// TODO Auto-generated destructor stub
}

//实现ParseParameter,simpleProcess函数
bool VoidApiHooker::parseParameter(){
	LOGD("parseParameter method has been called successfully in VoidApiHooker");
	return true;
}
bool VoidApiHooker::simpleProcess(){
	LOGD("simpleProcess method has been called successfully in VoidApiHooker");
	return true;
}
