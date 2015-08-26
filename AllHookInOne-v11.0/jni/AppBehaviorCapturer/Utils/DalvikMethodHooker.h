#ifndef __DalvikM_METHOD_HOOKER__H__
#define __Dalvik_METHOD_HOOKER__H__
//#include "../ApiHooker/ApiHooker.h"
#include "../System/ApiHookerManager.h"

#include "common.h"
#include "android_runtime/AndroidRuntime.h"
#include "dvm.h"
#include <unordered_map>
#include <jni.h>

#include "TimeUtils.h"
//#include "JniInternal.h"

ArrayObject* dvmGetMethodParamTypes(const Method* method,
		const char* methodsig);
ArrayObject* dvmBoxMethodArgs(const Method* method, const u4* args);
int dalvikJavaMethodHook(JNIEnv* env, ApiHooker* temp,HookInfo *info);

#endif //end of __JAVA_METHOD_HOOK__H__
