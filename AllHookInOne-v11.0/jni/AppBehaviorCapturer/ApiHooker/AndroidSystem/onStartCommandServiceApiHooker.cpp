/*
 * onStartCommandServiceApiHooker.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "onStartCommandServiceApiHooker.h"


onStartCommandServiceApiHooker::onStartCommandServiceApiHooker() {
	this->mApiDeclaration =
			*(new ApiDeclaration("android/app/Service", "onStartCommand",
					"(Landroid/content/Intent;II)I", false, NULL, NULL, NULL));

	LOGD("进入startcommand service");
}

onStartCommandServiceApiHooker::~onStartCommandServiceApiHooker() {
	// TODO Auto-generated destructor stub
}

/**
 * 该函数解析Service类的onStartCommand方法的参数
 * args[0]表示调用主体，也就是Service（或其子类）实例
 * 调用实例的toString方法，将其信息打印到logcat
 */
bool onStartCommandServiceApiHooker::parseParameter(const u4* args) {
	LOGD("[参数解析]开始解析onstart方法的调用实例");
	JNIEnv *env = AndroidRuntime::getJNIEnv();
	jclass service = env->FindClass("android/app/Service");
	if (service == 0) {
		LOGE("Get Class failed");
		return false;
	}

	jmethodID methodID = env->GetMethodID(service, "toString",
			"()Ljava/lang/String;");
	if (methodID == 0) {
		LOGE("get method failed");
		return false;
	}

	// 参数1
	Object* activityObject = (Object*) args[0];
	// 参数2
	Method* serviceToString = (Method*) methodID;
	// 参数3
	u4* uriArgs = (u4*) 1;
	ArrayObject* argList = dvmBoxMethodArgs(serviceToString, uriArgs);
	// 参数4
	ArrayObject* params = (ArrayObject *) dvmGetMethodParamTypes(
			serviceToString, "()Ljava/lang/String;");
	// 参数5
	ClassObject* returnType = (ClassObject *) dvmGetBoxedReturnType(
			serviceToString);
	// 调用这个方法
	Object* toStringResult = dvmInvokeMethod(activityObject, serviceToString,
			argList, params, returnType, true);

	StringObject* sourceNameObj = (StringObject*) toStringResult;
	char* paramString = dvmCreateCstrFromString(sourceNameObj);
	LOGD("[+] service调用实例为 %s", paramString);
	ApiHookerManager::getInstance()->mContextInfo = paramString;
	return true;

}
bool onStartCommandServiceApiHooker::parseResult(Object* obj) {
	char rs[20];
	int* ma ;
	int i = 0;
	ma = (int*) obj;
	i = reinterpret_cast<int>(&ma[0]);
	sprintf(rs, "%d", i);
	LOGD("[返回值解析] -> %s", rs);
	StringObject* stringObjId = dvmCreateStringFromCstr(rs);
	char* resultString = dvmCreateCstrFromString(stringObjId);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(resultString);
	return true;
}
