/*
 * OnStartActivityApiHooker.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "OnStartActivityApiHooker.h"

OnStartActivityApiHooker::OnStartActivityApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity","onStart","()V",
			false,NULL,NULL,NULL));

}

OnStartActivityApiHooker::~OnStartActivityApiHooker() {
	// TODO Auto-generated destructor stub
}

/**
 * 该函数解析Activity类的onCreate方法的参数
 * args[0]表示调用主体，也就是Activity（或其子类）实例
 * 调用实例的toString方法，将其信息打印到logcat
 */
bool OnStartActivityApiHooker::parseParameter(const u4* args) {
	LOGD("[参数解析]开始解析oncreate方法的调用实例");
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
	ArrayObject* params = (ArrayObject *) dvmGetMethodParamTypes(activityToString,"()Ljava/lang/String;");
	// 参数5
	ClassObject* returnType = (ClassObject *) dvmGetBoxedReturnType(activityToString);
	// 调用这个方法
	Object* toStringResult = dvmInvokeMethod(activityObject, activityToString, argList,
			params, returnType, true);

	StringObject* sourceNameObj = (StringObject*) toStringResult;
	char* paramString = dvmCreateCstrFromString(sourceNameObj);
	LOGD("[+] 调用实例为 %s", paramString);

	ApiHookerManager::getInstance()->mcontextinfo = paramString;
	return true;

}
