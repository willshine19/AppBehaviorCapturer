/*
 * OnResumeActivityApiHooker.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "OnResumeActivityApiHooker.h"

OnResumeActivityApiHooker::OnResumeActivityApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"onResume", "()V", false, NULL, NULL, NULL));

}

OnResumeActivityApiHooker::~OnResumeActivityApiHooker() {
	// TODO Auto-generated destructor stub
}

/**
 * 该函数解析Activity类的onCreate方法的参数
 * args[0]表示调用主体，也就是Activity（或其子类）实例
 * 调用实例的toString方法，将其信息打印到logcat
 */
bool OnResumeActivityApiHooker::parseParameter(const u4* args) {
	LOGD("[参数解析]开始解析onresume方法的调用实例");
	JNIEnv *env = AndroidRuntime::getJNIEnv();
	jclass activity = env->FindClass("android/app/Activity");
	if (activity == 0) {
		LOGE("Get Class failed");
		return false;
	}

	jmethodID methodID = env->GetMethodID(activity, "toString",
			"()Ljava/lang/String;");
	if (methodID == 0) {
		LOGE("get method failed");
		return false;
	}

	// 参数1
	Object* activityObject = (Object*) args[0];
	// 参数2
	Method* activityToString = (Method*) methodID;
	// 参数3
	u4* uriArgs = (u4*) 1;
	ArrayObject* argList = dvmBoxMethodArgs(activityToString, uriArgs);
	// 参数4
	ArrayObject* params = (ArrayObject *) dvmGetMethodParamTypes(
			activityToString, "()Ljava/lang/String;");
	// 参数5
	ClassObject* returnType = (ClassObject *) dvmGetBoxedReturnType(
			activityToString);
	// 调用这个方法，获取context
	Object* toStringResult = dvmInvokeMethod(activityObject, activityToString,
			argList, params, returnType, true);

	StringObject* sourceNameObj = (StringObject*) toStringResult;
	char* paramString = dvmCreateCstrFromString(sourceNameObj);
	LOGD("[+] OnResume调用实例为 %s", paramString);
	long threadId = pthread_self();	//获取c层的线程号
	(ThreadMap::getInstance()->mpid_contextMap).insert(
			make_pair(threadId, paramString));
	//zds测试
	auto mMapFound = (ThreadMap::getInstance()->mpid_contextMap).find(threadId);
	LOGD("存入hashmap中c线程号为 %ld", mMapFound->first);
	LOGD("存入hashmap中context为 %s", mMapFound->second);

	//zds
	ApiHookerManager::getInstance()->mcontextinfo = paramString;
	//直接赋值，用printf("%s",s1);输出是会出问题的。可以用printf("%s",s1.c_str())

	return true;

}
