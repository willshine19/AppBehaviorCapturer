#ifndef __DalvikM_METHOD_HOOKER__H__
#define __Dalvik_METHOD_HOOKER__H__
//#include "../ApiHooker/ApiHooker.h"
#include "../ApiHooker/StartThreadApiHooker.h"
#include "common.h"
#include "android_runtime/AndroidRuntime.h"
#include "dvm.h"
#include "../System/ApiHookerManager.h"
#include <typeinfo>
#include <unordered_map>

//#include "StartThread.h"

int dalvikJavaMethodHook(JNIEnv* env, ApiHooker* temp,HookInfo *info);

#endif //end of __JAVA_METHOD_HOOK__H__
