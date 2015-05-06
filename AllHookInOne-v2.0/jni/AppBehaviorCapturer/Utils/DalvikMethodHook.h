#ifndef __DalvikM_METHOD_HOOK__H__
#define __Dalvik_METHOD_HOOK__H__
//#include "StartThread.h"

extern int __attribute__ ((visibility ("hidden"))) dalvik_java_method_hook(
		JNIEnv* env, HookInfo *info);

#endif //end of __JAVA_METHOD_HOOK__H__
