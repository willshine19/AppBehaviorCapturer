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

	StartThreadApiHooker* start = new StartThreadApiHooker(new ApiDeclaration("java/lang/Thread","start","()V",false,NULL,NULL,NULL),new CollectedApiInfo());
	LOGD("startThreadApiHooker apiName is %s",start->getApiDeclaration().getApiName().c_str());


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
	HookInfo *info;
//	mApiHookerHashMap.begin();
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
	JavaMethodHook* mJavaMethodHook = new JavaMethodHook();
/*	for(遍历整个HashMap){4
		ApiDeclaration* apiDeclaration = start->getApiDeclaration();
		info->classDesc = apiDeclaration->getClassName();
		info->methodName = apiDeclaration->getApiName();
		info->methodSig = apiDeclaration->getApiSignature();
		info->isStaticMethod = apiDeclaration->isStaticMethod();
		info->originalMethod = apiDeclaration->getOriginalMethod();
		info->paramTypes = apiDeclaration->getParamTapes();
		info->returnType = apiDeclaration->getReturnType();
		LOGD("info->classDesc=%s",info->classDesc);
		LOGD("info->methodName=%s",info->methodName);
		LOGD("info->methodSig=%s",info->methodSig);
		LOGD("info->isStaticMethod=%c",info->isStaticMethod);
		mJavaMethodHook->hookJavaMethod(env,info);
	}*/

	LOGD("*-*-*-*-*-*-*- End -*-*-*-*-*-*-*-*-*-*");
	return true;
}
InfoSender* ApiHookerManager::getInfoSender(){
	if(mInfoSender != NULL){
		return this->mInfoSender;
	}
	return NULL;
}

