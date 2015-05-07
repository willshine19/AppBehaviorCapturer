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
	LOGD("construct ApiHookerManager success");
	// TODO Auto-generated constructor stub
}

ApiHookerManager::~ApiHookerManager() {
	// TODO Auto-generated destructor stub
}
//静态成员变量初始化
ApiHookerManager* ApiHookerManager::apiHookerManagerInstance = NULL;
//单例模式中访问实例的接口
ApiHookerManager* ApiHookerManager::getInstance(){
	if(apiHookerManagerInstance == NULL){
		apiHookerManagerInstance = new ApiHookerManager();
	}
	return apiHookerManagerInstance;
}

JNIEnv* ApiHookerManager::GetEnv()
{
	 //获取JavaVM，由此可获取JNIEnv
	 this->g_JavaVM = android::AndroidRuntime::getJavaVM();
	 LOGD("-------------Init succeed--------------\n");

    int status;
    JNIEnv *envnow = NULL;
    //使用指定的JNI版本，获取java环境
    status = g_JavaVM->GetEnv((void **)&envnow, JNI_VERSION_1_4);
    if(status < 0)
    {
    	//将当前C线程转为java线程
        status = g_JavaVM->AttachCurrentThread(&envnow, NULL);
        if(status < 0)
        {
            return NULL;
        }
    }
    LOGD("-------------getEnv succeed--------------\n");
    return envnow;
}
//系统初始化
bool ApiHookerManager::init(){
	LOGD("ApiHookerManager正在初始化");
	//获取系统发送模块的实例
	this->mInfoSender = InfoSender::getInstance();

	string s1 = "ads";
	LOGD("this is ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ %s",s1.data());
	LOGD("this is ------------------------------------------------------- %s",s1.c_str());
	//初始化系统中所有的ApiHooker，并将其装载至mApiHookerHashMap中
	initHashMap();
	bindJavaMethodToNative();
/*	StartThreadApiHooker* start = new StartThreadApiHooker(new ApiDeclaration("java/lang/Thread","start","()V",false,NULL,NULL,NULL),new CollectedApiInfo());
	LOGD("startThreadApiHooker apiName is %s",start->getApiDeclaration().getApiName().c_str());*/


//		HookInfo myinfo = {"java/lang/Thread", "start","()V", false, NULL, NULL, NULL};
		//HookInfo myinfo = {"android/app/Activity", "onCreate","(Landroid/os/Bundle;)V", false, NULL, NULL, NULL};
/*
		// 查找元素
		auto iElementFound = mApiHookerHashMap.find("start");
		if (iElementFound != mApiHookerHashMap.end())
		{
//			cout << "Found! Key " << endl;
//			cout	  << "key is " << iElementFound->first << endl;
			LOGD("Found key");
			ApiHooker temp = iElementFound->second ;
//			LOGD("value 中的ApiHooker为：%s",temp.toString());
			cout << "value 中的ApiHooker为： " << temp.toString() << endl;
			// 改动说明 ： 将ApiHooker 的成员属性 改为public 。VoidApiHooker StartThread中的成员属性 注释掉
		}
		else
			LOGD( "Key has no corresponding value in unordered map!");*/

		// 删除元素
/*		mApiHookerHashMap.erase("start");
		LOGD("Number of pairs,size is %d",mApiHookerHashMap.size());
		cout << "Number of pairs, size(): " << mApiHookerHashMap.size() << endl;*/


	return 0;
}
bool ApiHookerManager::initHashMap(){
	//所有的ApiHooker在这里实例化
	StartThreadApiHooker* start = new StartThreadApiHooker(new ApiDeclaration("java/lang/Thread","start","()V",false,NULL,NULL,NULL),new CollectedApiInfo());
	LOGD("startThreadApiHooker apiName is %s",start->getApiDeclaration().getApiName().c_str());
	// 将ApiHooker装填到HashMap中
	mApiHookerHashMap.insert(make_pair("start", *start));
	LOGD("insert element to hashmap succeed");
	return true;
}
bool ApiHookerManager::bindJavaMethodToNative(){
	//绑定Java方法到本地的代码
	JNIEnv *env = GetEnv();
	HookInfo info;
	JavaMethodHook* mJavaMethodHook = new JavaMethodHook();
	ApiHooker tempApiHooker;
	ApiDeclaration tempApiDeclaration;

	//取出哈西表的第一个元素
	unordered_map<string,ApiHooker>::iterator map_it = mApiHookerHashMap.begin();
	//哈西表每个ApiHooker的绑定过程
	while(map_it != mApiHookerHashMap.end()){
		LOGD("step 1");
		//获取哈西表中的键值
		LOGD("===============%s",map_it->first.data());//这个地方的输出是正确的，输出start
		tempApiHooker = (ApiHooker)map_it->second;
		LOGD("step 2");
		if(&tempApiHooker== NULL){
			LOGE("AiHookerManager bindJavaMethodToNative failed");
			break;
		}else{
			LOGD("get ApiHooker in mApiHookerHashMap succeed");
			tempApiDeclaration = tempApiHooker.getApiDeclaration();
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
			mJavaMethodHook->hookJavaMethod(env,&info);
			++map_it;
			LOGD("step 4");
		}

	}
/*	// 查找元素
	auto iElementFound = mApiHookerHashMap.find("start");
	if (iElementFound != mApiHookerHashMap.end())
	{
		LOGD("Found key");
		ApiHooker temp = iElementFound->second ;
//			LOGD("value 中的ApiHooker为：%s",temp.toString());
		cout << "value 中的ApiHooker为： " << temp.toString() << endl;
		// 改动说明 ： 将ApiHooker 的成员属性 改为public 。VoidApiHooker StartThread中的成员属性 注释掉
	}
	else
		LOGD( "Key has no corresponding value in unordered map!");*/

	LOGD("*-*-*-*-*-*-*- End -*-*-*-*-*-*-*-*-*-*");
	return true;
}
InfoSender* ApiHookerManager::getInfoSender(){
	if(mInfoSender != NULL){
		return this->mInfoSender;
	}
	return NULL;
}

