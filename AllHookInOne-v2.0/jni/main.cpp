#include <jni.h>
#include <dlfcn.h>
#include <string.h>
#include "android_runtime/AndroidRuntime.h"

#include "common.h"
#include "AppBehaviorCapturer/Utils/JavaMethodHook.h"
#include "AppBehaviorCapturer/System/ApiHookerManager.h"


extern "C" void InjectInterface(char*arg){
	LOGD("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	LOGD("*-*-*-*-*-* Injected so *-*-*-*-*-*-*-*");
	LOGD("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
	//获取ApiHookerManager的实例，ApiHookerManager采用单例模式
	ApiHookerManager* apiHookerManager = ApiHookerManager::getInstance();
	//完成系统的初始化
	apiHookerManager->init();
}
static inline void get_cstr_from_jstring(JNIEnv* env, jstring jstr, char **out) {
	jboolean iscopy = JNI_TRUE;
	const char *cstr = env->GetStringUTFChars(jstr, &iscopy);
	*out = strdup(cstr);
	env->ReleaseStringUTFChars(jstr, cstr);
}

typedef int (*strlen_fun)(const char *);
strlen_fun old_strlen = NULL;

size_t my_strlen(const char *str){
	LOGI("strlen was called.");
	int len = old_strlen(str);
	return len * 2;
}

strlen_fun global_strlen1 = (strlen_fun)strlen;
strlen_fun global_strlen2 = (strlen_fun)strlen;


