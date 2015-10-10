/*
 * OnCreateActivityApiHooker.cpp
 *
 *  Created on: 2015-5-12
 *      Author: long
 */

#include "OnCreateActivityApiHooker.h"

OnCreateActivityApiHooker::OnCreateActivityApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"onCreate","(Landroid/os/Bundle;)V", false, NULL, NULL, NULL));
//	this->mCollectedApiInfo = *(new CollectedApiInfo());
}

OnCreateActivityApiHooker::~OnCreateActivityApiHooker() {
	// TODO Auto-generated destructor stub
}

bool OnCreateActivityApiHooker::parseParameter(const u4* args) {
	LOGD("开始解析oncreate方法的调用实例");
	JNIEnv *env = AndroidRuntime::getJNIEnv();
	jclass activity = env->FindClass("android/app/Activity");
	if (activity == 0) {
		LOGE("Get Class failed");
		return false;
	}
	LOGD("Find class successfully");

	jmethodID methodID = env->GetMethodID(activity, "toString",
			"()Ljava/lang/String;");
	if (methodID == 0) {
		LOGE("get method failed");
		return false;
	}
	LOGD("get method successfully");

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
	return true;

}


