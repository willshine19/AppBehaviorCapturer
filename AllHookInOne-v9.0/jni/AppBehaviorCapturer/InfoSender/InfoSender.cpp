/*
 * InfoSender.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */
#include "InfoSender.h"
using namespace std;

InfoSender::InfoSender(BlockingQueue* blockingQueue) {
	// TODO Auto-generated constructor stub
	cout << "construct InfoSender success " << endl;
//	this->mCycledBlockingQueue = blockingQueue;
	pthread_mutex_init(&InfoSender::lock, NULL);
}

InfoSender::~InfoSender() {
	// TODO Auto-generated destructor stub
}

//静态成员变量初始化
InfoSender* InfoSender::infoSenderInstance = NULL;
int InfoSender::sockfd = 0;
CycledBlockingQueue* InfoSender::mCycledBlockingQueue = NULL;
pthread_mutex_t InfoSender::lock = PTHREAD_MUTEX_INITIALIZER;;
//CycledBlockingQueue* mCycledBlockingQueue
//单例模式中访问实例的接口
InfoSender* InfoSender::getInstance(){
	pthread_mutex_lock(&InfoSender::lock);
	if(infoSenderInstance == NULL){
		BlockingQueue *q = new CycledBlockingQueue();
		infoSenderInstance = new InfoSender(q);
	}
	pthread_mutex_unlock(&InfoSender::lock);
	return infoSenderInstance;
}
void* InfoSender::readFromQueue(void* arg){
	LOGD("create reading thread successfully");
	int count;
//	const char* s;
	string s;
	while(1){
		LOGD("第 %d 次 发送JSon",count);
		CollectedApiInfo temp = InfoSender::mCycledBlockingQueue->send();
		s = temp.convertToJson();

//		JNIEnv *env = AndroidRuntime::getJNIEnv();
//		jstring js1 = env->NewStringUTF(s);
//		jstring js2 = env->NewStringUTF("nihao");
		string s1 = "hello";
		Json::Value root;
//		root[js1] = 2;
//		root.Value(1);
//		string rr = root.toStyledString();
//		int len = sizeof(rr);
		//在此处添加发送json
//		int len = s1.size();
		int len = s.size();

		int result = (int) send(sockfd, s.c_str(), len, 0);
		LOGD("send Json successfully");
		if (result == -1)
			LOGE("[-]send Json error!\r\n");
		++count;
	}
	return ((void*)0);
}
int InfoSender::socketConnection(){
	//创建并初始化socket链接
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
//成员函数后面在做补充
bool InfoSender::init(){
	//初始化队列
	InfoSender::mCycledBlockingQueue = new CycledBlockingQueue(1024);
//	this->mCycledBlockingQueue = new CycledBlockingQueue(1024);
	//初始化读线程
	int err = pthread_create(&this->ntid,NULL,InfoSender::readFromQueue,NULL);
	if(err !=0){
		LOGE("can not create thread :%s",strerror(err));
	}
	socketConnection();
	return true;
}
/*CycledBlockingQueue* InfoSender::getCycledBlockingQueue(){
	return this->mCycledBlockingQueue;
}*/

