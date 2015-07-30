/*
 * InfoSender.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef INFOSENDER_H_
#define INFOSENDER_H_
#include "../InfoSender/CycledBlockingQueue.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "android_runtime/AndroidRuntime.h"
#include "../Utils/TimeUtils.h"
#include "../Utils/json/json/json.h"

using android::AndroidRuntime;
class InfoSender {
	private:
	//	BlockingQueue<CollectedApiInfo> mCycledBlockingQueue;
	//需将BlockingQueue做成模板

	static InfoSender* infoSenderInstance;
	pthread_t ntid;
	static int sockfd;
	//使用单例模式，构造方法私有，声明一个private static变量，由getInstance方法访问
	InfoSender(BlockingQueue* blockingQueue);
	virtual ~InfoSender();

	public:
		static InfoSender* getInstance();
		static void* readFromQueue(void* arg);
		static CycledBlockingQueue* mCycledBlockingQueue;
//		static BlockingQueue* mCycledBlockingQueue;
		static pthread_mutex_t lock;
		//成员函数，需填写响应逻辑
		bool init();
//		void* readFromQueue();
		int socketConnection();
//		bool send();跟系统中的send方法重名，不可用
		CycledBlockingQueue* getCycledBlockingQueue();
};

#endif /* INFOSENDER_H_ */
