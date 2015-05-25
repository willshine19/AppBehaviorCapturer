/*
 * InfoSender.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */
#include <iostream>
#include "InfoSender.h"
using namespace std;

InfoSender::InfoSender(BlockingQueue* blockingQueue) {
	// TODO Auto-generated constructor stub
	cout << "construct InfoSender success " << endl;
//	this->mCycledBlockingQueue = blockingQueue;
}
/*InfoSender::InfoSender() {
	// TODO Auto-generated constructor stub
	cout << "construct InfoSender success " << endl;
//	this->mCycledBlockingQueue = blockingQueue;
}*/

InfoSender::~InfoSender() {
	// TODO Auto-generated destructor stub
}

//静态成员变量初始化
InfoSender* InfoSender::infoSenderInstance = NULL;
//单例模式中访问实例的接口
InfoSender* InfoSender::getInstance(){
	if(infoSenderInstance == NULL){
		BlockingQueue *q = new CycledBlockingQueue();
		infoSenderInstance = new InfoSender(q);
	}
	return infoSenderInstance;
}
int InfoSender::socketConnection(){
	return 1;
}
bool send(){
	return true;
}
//成员函数后面在做补充
