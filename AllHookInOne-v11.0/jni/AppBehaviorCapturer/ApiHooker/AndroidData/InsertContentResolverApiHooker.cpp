/*
 * InsertContentResolverApiHooker.cpp
 *
 *  Created on: 2015-6-16
 *      Author: long
 */

#include "InsertContentResolverApiHooker.h"

using namespace android;
InsertContentResolverApiHooker::InsertContentResolverApiHooker() {
	// TODO Auto-generated constructor stub
	this->mApiDeclaration = *(new ApiDeclaration("android/content/ContentResolver",
			"insert","(Landroid/net/Uri;Landroid/content/ContentValues;)Landroid/net/Uri;",false,NULL,NULL,NULL));
}

InsertContentResolverApiHooker::~InsertContentResolverApiHooker() {
	// TODO Auto-generated destructor stub
}

bool InsertContentResolverApiHooker::parseParameter(const u4* args){
	LOGD("Begin parse parameter Uri");
	//解析Uri参数测试逻辑
	JNIEnv *env = AndroidRuntime::getJNIEnv();
	jclass uri = env->FindClass("android/net/Uri");
	if (uri == 0) {
		LOGE("Get Uri Class failed");
	}
	LOGD("Find Uri class successfully");

	jmethodID methodID = env->GetMethodID(uri, "toSafeString",
			"()Ljava/lang/String;");
	if (methodID == 0) {
		LOGE("get uri toSafeString method failed");
	}
	LOGD("get toSafeString method successfully");

	// 参数1
	Object* uriObject = (Object*) args[1];
	// 参数2
	Method* uriToString = (Method*) methodID;
	// 参数3
	u4* uriArgs = (u4*)1;
	ArrayObject* uriArgTypes = dvmBoxMethodArgs(uriToString, uriArgs);
	// 参数4
	ArrayObject* params = (ArrayObject *) dvmGetMethodParamTypes(uriToString,"()Ljava/lang/String;");
	// 参数5
	ClassObject* returnType = (ClassObject *) dvmGetBoxedReturnType(uriToString);
	// 调用这个方法
	Object* uriResult = dvmInvokeMethod(uriObject, uriToString, uriArgTypes,
			params, returnType, true);

	StringObject* sourceNameObj = (StringObject*) uriResult;
	char* paramString = dvmCreateCstrFromString(sourceNameObj);
	LOGD("paramString is %s",paramString);
	LOGD("parse parameter uri successfully");
	return true;
}

bool InsertContentResolverApiHooker::parseResult(Object* obj) {
	JNIEnv *env = AndroidRuntime::getJNIEnv();
		jclass uri = env->FindClass("android/net/Uri");
		if (uri == 0) {
			LOGE("Get Uri Class failed");
		}
		LOGD("Find Uri class successfully");

		jmethodID methodID = env->GetMethodID(uri, "toSafeString",
				"()Ljava/lang/String;");
		if (methodID == 0) {
			LOGE("get uri toSafeString method failed");
		}
		LOGD("get toSafeString method successfully");

		// 参数2
		Method* uriToString = (Method*) methodID;
		// 参数3
		u4* uriArgs = (u4*)1;
		ArrayObject* uriArgTypes = dvmBoxMethodArgs(uriToString, uriArgs);
		// 参数4
		ArrayObject* params = (ArrayObject *) dvmGetMethodParamTypes(uriToString,"()Ljava/lang/String;");
		// 参数5
		ClassObject* returnType = (ClassObject *) dvmGetBoxedReturnType(uriToString);
		// 调用这个方法
		Object* uriResult = dvmInvokeMethod(obj, uriToString, uriArgTypes,
				params, returnType, true);

		StringObject* sourceNameObj = (StringObject*) uriResult;
		char* resultString = dvmCreateCstrFromString(sourceNameObj);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(resultString);
	return true;
}

