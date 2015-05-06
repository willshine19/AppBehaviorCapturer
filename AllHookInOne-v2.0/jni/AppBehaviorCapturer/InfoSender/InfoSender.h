/*
 * InfoSender.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef INFOSENDER_H_
#define INFOSENDER_H_
#include "../InfoSender/CycledBlockingQueue.h"

class InfoSender {
	private:
	//	BlockingQueue<CollectedApiInfo> mCycledBlockingQueue;
	//需将BlockingQueue做成模板
	BlockingQueue mCycledBlockingQueue;
	static InfoSender* infoSenderInstance;
	//使用单例模式，构造方法私有，声明一个private static变量，由getInstance方法访问
	InfoSender(BlockingQueue* blockingQueue);
	virtual ~InfoSender();

	public:
		static InfoSender* getInstance();

		//成员函数，需填写响应逻辑
		bool init();
		int socketConnection();
		bool send();
};

#endif /* INFOSENDER_H_ */
