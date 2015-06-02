/*
 * ApiHookerManager.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "ApiHookerManager.h"

#include <iostream>
using namespace std;
using namespace __gnu_cxx;
ApiHookerManager::ApiHookerManager() {
	LOGD("construct ApiHookerManager successfully");
	// TODO Auto-generated constructor stub
	pthread_mutex_init(&ApiHookerManager::lock, NULL);
}

ApiHookerManager::~ApiHookerManager() {
	// TODO Auto-generated destructor stub
}
//静态成员变量初始化
ApiHookerManager* ApiHookerManager::apiHookerManagerInstance = NULL;
pthread_mutex_t ApiHookerManager::lock = PTHREAD_MUTEX_INITIALIZER;;
//单例模式中访问实例的接口
ApiHookerManager* ApiHookerManager::getInstance(){
	pthread_mutex_lock(&ApiHookerManager::lock);
	if(apiHookerManagerInstance == NULL){
		apiHookerManagerInstance = new ApiHookerManager();
	}
	pthread_mutex_unlock(&ApiHookerManager::lock);
	return apiHookerManagerInstance;
}

JNIEnv* ApiHookerManager::getEnv()
{
	 //获取JavaVM，由此可获取JNIEnv
	 this->mJavaVM = android::AndroidRuntime::getJavaVM();
	 LOGD("-------------Init successfully--------------\n");

    int status;
    JNIEnv *envnow = NULL;
    //使用指定的JNI版本，获取java环境
    status = mJavaVM->GetEnv((void **)&envnow, JNI_VERSION_1_4);
    if(status < 0)
    {
    	//将当前C线程转为java线程
        status = mJavaVM->AttachCurrentThread(&envnow, NULL);
        if(status < 0)
        {
            return NULL;
        }
    }
    LOGD("-------------getEnv successfully--------------\n");
    return envnow;
}
//系统初始化
bool ApiHookerManager::init(){
	LOGD("AppBehaviorCapturer system V7.0 is running");
	//初始化系统中所有的ApiHooker，并将其装载至mApiHookerHashMap中
	initHashMap();
	bindJavaMethodToNative();
	//获取系统发送模块的实例
	this->mInfoSender = InfoSender::getInstance();
	//初始化发送模块
	mInfoSender->init();
	// 删除元素
/*		mApiHookerHashMap.erase("start");
	LOGD("Number of pairs,size is %d",mApiHookerHashMap.size());
	cout << "Number of pairs, size(): " << mApiHookerHashMap.size() << endl;*/
	return 0;
}
bool ApiHookerManager::initHashMap(){
	//所有的ApiHooker在这里实例化
	StartThreadApiHooker* start = new StartThreadApiHooker();
	if(typeid(*start) == typeid(StartThreadApiHooker)){
		LOGD("start is StartThreadApiHooker");//输出结果是正确的
	}
	OnCreateActivityApiHooker* onCreate = new OnCreateActivityApiHooker();
	GetMacAddressWifiInfoApiHooker* getMacAddress = new GetMacAddressWifiInfoApiHooker();
	RunThreadApiHooker* run = new RunThreadApiHooker();
	GetLastKnownLocationApiHooker* getLastKnownLocation = new GetLastKnownLocationApiHooker();
	GetDeviceIdTelephonyApiHooker* getDeviceId =new GetDeviceIdTelephonyApiHooker();
	// 将ApiHooker装填到HashMap中
	mApiHookerHashMap.insert(make_pair("start", start));
	LOGD("insert StartThreadApiHooker to hashmap successfully");
	mApiHookerHashMap.insert(make_pair("onCreate", onCreate));
	LOGD("insert OnCreateActivityApiHooker to hashmap successfully");
/*	mApiHookerHashMap.insert(make_pair("getMacAddress",getMacAddress));
	LOGD("insert getMacAddress to hashmap successfully");*/
	mApiHookerHashMap.insert(make_pair("run", run));
	LOGD("insert RunThreadApiHooker to hashmap successfully");
	mApiHookerHashMap.insert(make_pair("getLastKnownLocation",getLastKnownLocation));
	LOGD("insert GetLastKnownLocationApiHooker to hashmap successfully");
	mApiHookerHashMap.insert(make_pair("getDeviceId",getDeviceId));
	LOGD("insert GetDeviceIdTelephonyApiHooker to hashmap successfully");

	return true;
}
bool ApiHookerManager::bindJavaMethodToNative(){
	//绑定Java方法到本地的代码
	JNIEnv *env = getEnv();
	HookInfo info;
	JavaMethodHooker* mJavaMethodHook = new JavaMethodHooker();
	ApiHooker* tempApiHooker;
	ApiDeclaration tempApiDeclaration;

	//取出哈西表的第一个元素
	unordered_map<string,ApiHooker*>::iterator map_it = mApiHookerHashMap.begin();
	//哈西表每个ApiHooker的绑定过程
	while(map_it != mApiHookerHashMap.end()){
		LOGD("step 1");
		//获取哈西表中的键值
		LOGD("===============%s",map_it->first.data());//这个地方的输出是正确的，输出start
		tempApiHooker = map_it->second;
		LOGD("step 2");
		if(&tempApiHooker== NULL){
			LOGE("AiHookerManager bindJavaMethodToNative failed");
			break;
		}else{
			LOGD("get ApiHooker in mApiHookerHashMap successfully");
			tempApiDeclaration = tempApiHooker->getApiDeclaration();
			info.classDesc = tempApiDeclaration.getClassName().c_str();
			LOGD("info classDesc is %s",info.classDesc);
			info.methodName = tempApiDeclaration.getApiName().c_str();
			LOGD("info methodName=%s",info.methodName);
			info.methodSig = tempApiDeclaration.getApiSignature().c_str();
			LOGD("info methodSig=%s",info.methodSig);
			info.isStaticMethod = tempApiDeclaration.isStaticMethod();
			LOGD("info isStaticMethod=%c",info.isStaticMethod);
			info.originalMethod = tempApiDeclaration.getOriginalMethod();
			info.paramTypes = tempApiDeclaration.getParamTapes();
			info.returnType = tempApiDeclaration.getReturnType();
			LOGD("step 3");
			mJavaMethodHook->hookJavaMethod(env,tempApiHooker,&info);
			++map_it;
			LOGD("step 4");
		}
	}
	LOGD("*-*-*-*-*-*-*- End -*-*-*-*-*-*-*-*-*-*");
	return true;
}
InfoSender* ApiHookerManager::getInfoSender(){
	if(mInfoSender != NULL){
		return this->mInfoSender;
	}
	return NULL;
}

