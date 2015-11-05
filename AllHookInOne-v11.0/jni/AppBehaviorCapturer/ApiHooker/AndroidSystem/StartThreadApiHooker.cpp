/*
 * StartThreadApiHooker.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "StartThreadApiHooker.h"

StartThreadApiHooker::StartThreadApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("java/lang/Thread", "start",
			"()V", false, NULL, NULL, NULL));
//	this->mCollectedApiInfo = *(new CollectedApiInfo());
}

StartThreadApiHooker::~StartThreadApiHooker() {
	// TODO Auto-generated destructor stub
}

/**
 * 该函数用于解析Thread类Start方法的参数
 * args[0]表示调用实例，也就是Thread实例（子线程）
 * 调用子线程getId()方法，得到一个线程号（long类型）
 * 再调用线程号的toString()方法，得到String类型的线程号，打印到logcat
 */
bool StartThreadApiHooker::parseParameter(const u4* args) {
	// 调用子线程的getId
	LOGD("[参数解析]调用Thread实例的getId");
	// 参数1
	Object* obj = (Object*) args[0];
	// 参数2
	JNIEnv *env = AndroidRuntime::getJNIEnv();
	jclass thread = env->FindClass("java/lang/Thread");
	if (thread == 0) {
		LOGE("Get Class failed");
	}

	jmethodID methodID = env->GetMethodID(thread, "getId", "()J");
	if (methodID == 0) {
		LOGE("get method failed");
	}
	Method* method = (Method*) methodID;
	// 参数3
	u4* uriArgs = (u4*) 1;
	ArrayObject* argList = dvmBoxMethodArgs(method, uriArgs);
	// 参数4
	ArrayObject* params = (ArrayObject *) dvmGetMethodParamTypes(method, "()J");
	// 参数5
	ClassObject* returnType = (ClassObject *) dvmGetBoxedReturnType(method);
	// 调用getId方法
	Object* longId = dvmInvokeMethod(obj, method, argList, params, returnType,
			true);

	// 调用Long对象的toString方法
	LOGD("[参数解析]调用Long实例的toSring");
	// 参数1 longId
	// 参数2
	jclass longclass = env->FindClass("java/lang/Long");
	if (longclass == 0) {
		LOGE("Get Class failed");
	}

	methodID = env->GetMethodID(longclass, "toString", "()Ljava/lang/String;");
	if (methodID == 0) {
		LOGE("get method failed");
	}
	method = (Method*) methodID;
	// 参数3
	argList = dvmBoxMethodArgs(method, uriArgs);
	// 参数4
	params = (ArrayObject *) dvmGetMethodParamTypes(method,
			"()Ljava/lang/String;");
	// 参数5
	returnType = (ClassObject *) dvmGetBoxedReturnType(method);
	// 调用toString方法
	Object* stringId = dvmInvokeMethod(longId, method, argList, params,
			returnType, true);

	StringObject* stringObjId = (StringObject*) stringId;
	char* paramString = dvmCreateCstrFromString(stringObjId);

	//zds add
		LOGD("doing hashmap");
		long threadId = pthread_self();	//获取c层的线程号
		long javaThreadId = 0;		//用来保存java层的线程号
		sscanf(paramString, "%ld", &javaThreadId);
		//将父的c和子的java的线程号存入hashmap中
	(ThreadMap::getInstance()->mMap).insert(make_pair(javaThreadId, threadId));
		//打印刚刚存入的键值对
		auto mMapFound = (ThreadMap::getInstance()->mMap).find(javaThreadId);
//		LOGD("[+] 存入hashmap中子java线程号为 %ld", mMapFound->first);
//		LOGD("[+] 存入hashmap中父c线程号为 %ld", mMapFound->second);

		LOGD("[+] start线程号为 %s", paramString);
		//end

	return true;
}

