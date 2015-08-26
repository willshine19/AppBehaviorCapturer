/*
 * InfoSender.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */
#include "InfoSender.h"
using namespace std;

/**
 * 构造函数
 * 参数：BlockingQueue实例的指针
 * 18行为什么注释掉了？
 * mCycledBlockingQueue已经改为类变量，在init()方法中初始化
 */
InfoSender::InfoSender(BlockingQueue* blockingQueue) {
	// TODO Auto-generated constructor stub
	cout << "construct InfoSender success " << endl;
//	this->mCycledBlockingQueue = blockingQueue;
	pthread_mutex_init(&InfoSender::lock, NULL);
}

/**
 * 析构函数
 */
InfoSender::~InfoSender() {
	// TODO Auto-generated destructor stub
}

//静态成员变量初始化
InfoSender* InfoSender::infoSenderInstance = NULL;
int InfoSender::sockfd = 0;
CycledBlockingQueue* InfoSender::mCycledBlockingQueue = NULL;
pthread_mutex_t InfoSender::lock = PTHREAD_MUTEX_INITIALIZER;
;
//CycledBlockingQueue* mCycledBlockingQueue

/**
 * 单例模式
 * 返回：唯一的InfoSender实例
 */
InfoSender* InfoSender::getInstance() {
	pthread_mutex_lock(&InfoSender::lock);
	if (infoSenderInstance == NULL) {
		BlockingQueue *q = new CycledBlockingQueue();
		infoSenderInstance = new InfoSender(q);
	}
	pthread_mutex_unlock(&InfoSender::lock);
	return infoSenderInstance;
}

/**
 * 从队列中读取CollectedApiInfo实例，发送json字符串到socket
 * 在新的线程中执行该函数
 */
void* InfoSender::readFromQueue(void* arg) {
	LOGD("create reading thread successfully");
	int count;
	TimeUtils* timeUtils = TimeUtils::getInstance();
	string s;//待发送的json字符串

	while (1) {
		LOGD("第 %d 次 发送JSon", count);
		// 若队列为空则阻塞
		CollectedApiInfo temp = InfoSender::mCycledBlockingQueue->send();
		s = temp.convertToJson();

		//发送json字符串
		int len = s.size();
		// send a message on a socket
		// ssize_t send(int socket, const void *buffer, size_t length, int flags);
		int result = (int) send(sockfd, s.c_str(), len, 0);
		LOGD("send Json successfully");
		if (result == -1)
			LOGE("[-]send Json error!\r\n");
		++count;
		//关于时间测试，为什么还用json传输，在这里做过一部分的探究，基于
		//结果是一样的
//		char* buf = new char[100];
//		strcpy(buf,"hello world");
//		send(sockfd, buf,buf->len, 0);
		//结果是一样的
//		string hello = "hello";
//		int ceshi = hello.length();
//		send(sockfd, hello.c_str(), ceshi, 0);
		//在此处发送t1_start_handle_string[0],完全可以发送出去，但是后面依然会跟一个{,和下面的情况一致
//		send(sockfd, timeUtils->t1_start_handle_string[0].c_str(), timeUtils->t1_start_handle_string[0].length(), 0);
//		LOGD("t1_start_handle_string[0]'s length is  %d",timeUtils->t1_start_handle_string[0].length());
		//时间测试，记录处理Api的结束时间，即t2
		timeUtils->setT2EndTime();

		//当已发送了CESHI_NUMBER个Json字符串后，即可计算时间差值等，然后发送至HookerManager
		if (count % CESHI_NUMBER == 0) {
			LOGD("begin calculate time subtract and send ");
			//开始计算时间差值，存入数组，计算平均值，并发送至HookerManager中
			string ss;
			//计算时间差值的总和，此处需要分两个地方存储，因为timeval结构体有两个成员,均为long类型
			long sum_timeval_time = 0L;
			long sum_timeval_seconds = 0L;
			//计算时间差值，并保存至对应的string数组
			for (int t = 0; t < CESHI_NUMBER; t++) {
				if (timeUtils->timevalSubtract(&timeUtils->time_subtract[t],
						&timeUtils->t2_end_handle_tv[t],
						&timeUtils->t1_start_handle_tv[t]) == 0) {
					//计算时间差值的总和
					sum_timeval_time += timeUtils->time_subtract[t].tv_sec;
//					LOGD("sum_timeval_time is %ud",sum_timeval_time);
					sum_timeval_seconds += timeUtils->time_subtract[t].tv_usec;
//					LOGD("sum_timeval_seconds is %ud",sum_timeval_seconds);
					ss = timeUtils->timevalToString(
							&timeUtils->time_subtract[t]);
					//保存时间差值对应的string数组
					timeUtils->time_subtract_string[t] = ss;
				}
			} // end for
			//将string输出，经验证，保存正常
			for (int i = 0; i < CESHI_NUMBER; i++) {
				LOGD(
						"[time test] timeSubtract is %s", timeUtils->time_subtract_string[i].c_str());
			}
			timeUtils->avg_time_subtract.tv_sec = sum_timeval_time
					/ CESHI_NUMBER;
			timeUtils->avg_time_subtract.tv_usec = sum_timeval_seconds
					/ CESHI_NUMBER;
			timeUtils->avg_time_subtract_string = timeUtils->timevalToString(
					&timeUtils->avg_time_subtract);
			LOGD("时间平均值  %s", timeUtils->avg_time_subtract_string.c_str());

			/*采用json格式发送时间测试结果，格式如下：
			 *Json::Value time_test;
			 time_test["t1-time"] = "t1-time";
			 time_test["t2-time"] = "t2-time";
			 time_test["t2-t1"] = "t2-t1";
			 time_test["avg(t2-t1)"] = "avg(t2-t1)";
			 string out = time_test.toStyledString();
			 send(sockfd, out.c_str(), out.length(), 0);
			 */
			Json::Value time_test;
			for (int i = 0; i < CESHI_NUMBER; i++) {
				time_test["t1_time"] = timeUtils->t1_start_handle_string[i];
				time_test["t2_time"] = timeUtils->t2_end_handle_string[i];
				time_test["t2_t1_subtract_time"] =
						timeUtils->time_subtract_string[i];
				time_test["avg_t2_t1"] = timeUtils->avg_time_subtract_string;

				//发送时间测试的json包
				string out = time_test.toStyledString();
				int result = (int) send(sockfd, out.c_str(), out.length(), 0);
				if (result == -1) {
					LOGE("send t1 error");
				}
			}
			/*			string t1;
			 //将t1存入json
			 //在此处一个时间是用;分割，便于在java程序端做解析
			 for(int i = 0;i < CESHI_NUMBER;i++){
			 t1.append(timeUtils->t1_start_handle_string[i]).append(";");
			 LOGD("t1 is %d",t1.c_str());
			 }
			 time_test["t1_time"] = t1;

			 //将t2存入json
			 string t2;
			 for(int i = 0;i < CESHI_NUMBER;i++){
			 t2.append(timeUtils->t2_end_handle_string[i]).append(";");
			 LOGD("t2 is %d",t2.c_str());
			 }
			 time_test["t2_time"] = t2;

			 //将t2-t1存入json
			 string t2_t1;
			 for(int i = 0;i < CESHI_NUMBER;i++){
			 t2_t1.append(timeUtils->time_subtract_string[i]).append(";");
			 LOGD("t2 is %d",t2_t1.c_str());
			 }
			 time_test["t2_t1_subtract_time"] = t2_t1;
			 //将avg(t2-t1)存入json
			 time_test["avg_t2_t1"] = timeUtils->avg_time_subtract_string;

			 //发送时间测试的json包
			 string out = time_test.toStyledString();
			 int result = (int)send(sockfd, out.c_str(), out.length(), 0);
			 if(result == -1){
			 LOGE("send t1 error");
			 }*/
		} // end if
	} // end while
	return ((void*) 0);
}

/**
 * 创建 并 初始化 socket链接
 * #include <sys/socket.h>
 */
int InfoSender::socketConnection() {
	int res;
	ssize_t cnt;
	int j;
	int k = 7; //(int)argv[1];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	LOGD("[+]create socket successfully");
	if (sockfd == -1) {
		perror("套接字创建失败\n");
		exit(1);
	}
	struct sockaddr_in servaddr;

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8821);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	LOGD("[+]configure socket successfully");

	res = connect(sockfd, (struct sockaddr *) &servaddr,
			sizeof(struct sockaddr));

	if (res == -1) {
		printf("accept error!\r\n");
	}
	/*	LOGD("send data");
	 char msg[1024 * 1] = "";
	 for (j = 0; j < (32 * 1); j++) {
	 //初始化32 个there is thirty-two chars.......
	 sprintf(msg, "%s%s", msg, "there is thirty-two chars.......");
	 }
	 int len, i;
	 int bytes_sent[103];
	 //发送5次msg
	 for (i = 0; i < 5; i++) {
	 char s[1050 * 1] = "";
	 sprintf(s, "%s%d\n", msg, i);
	 len = strlen(s);
	 bytes_sent[i] = send(sockfd, s, len, 0);
	 if (bytes_sent[i] == -1)
	 printf("send bytes error!\r\n");
	 }
	 close(res);
	 while (waitpid(-1, NULL, WNOHANG) > 0);*/
	return 0;
}

/**
 * 类的初始化
 * 成员函数后面在做补充
 */
bool InfoSender::init() {
	//初始化队列
	InfoSender::mCycledBlockingQueue = new CycledBlockingQueue(1024);
//	this->mCycledBlockingQueue = new CycledBlockingQueue(1024);
	//初始化读线程
	int err = pthread_create(&this->ntid, NULL, InfoSender::readFromQueue,
			NULL);
	if (err != 0) {
		LOGE("can not create thread :%s", strerror(err));
	}
	socketConnection();
	return true;
}
/*CycledBlockingQueue* InfoSender::getCycledBlockingQueue(){
 return this->mCycledBlockingQueue;
 }*/

