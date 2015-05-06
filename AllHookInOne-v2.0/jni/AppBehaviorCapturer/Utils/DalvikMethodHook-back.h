/*

 * DalvikMethodHook.h
 *
 *  Created on: 2015-4-28
 *      Author: long


#ifndef DALVIKMETHODHOOK_H_
#define DALVIKMETHODHOOK_H_

#include "common.h"
#include "JavaMethodHook.h"
#include "android_runtime/AndroidRuntime.h"
#include "dvm.h"

class DalvikMethodHook {
public:
	HookInfo save;
	DalvikMethodHook();
	virtual ~DalvikMethodHook();

	static int calcMethodArgsSize(const char* shorty);
	static u4 dvmPlatformInvokeHints(const char* shorty);
	static int dvmComputeJniArgInfo(const char* shorty);
	static jclass dvmFindJNIClass(JNIEnv *env, const char *classDesc);
	static ClassObject* dvmFindClass(const char *classDesc);
	static ArrayObject* dvmBoxMethodArgs(const Method* method, const u4* args);
	static ArrayObject* dvmGetMethodParamTypes(const Method* method,
			const char* methodsig);
	static void method_handler(const u4* args, JValue* pResult,
			const Method* method, struct Thread* self);
	static int __attribute__ ((visibility ("hidden"))) dalvik_java_method_hook(
			JNIEnv* env, HookInfo *info);
	int calcMethodArgsSize(const char* shorty);
	u4 dvmPlatformInvokeHints(const char* shorty);
	int dvmComputeJniArgInfo(const char* shorty);
	jclass dvmFindJNIClass(JNIEnv *env, const char *classDesc);
	ClassObject* dvmFindClass(const char *classDesc);
	ArrayObject* dvmBoxMethodArgs(const Method* method, const u4* args);
	ArrayObject* dvmGetMethodParamTypes(const Method* method,
			const char* methodsig);
	void method_handler(const u4* args, JValue* pResult,
			const Method* method, struct Thread* self);


};

#endif  DALVIKMETHODHOOK_H_
*/
