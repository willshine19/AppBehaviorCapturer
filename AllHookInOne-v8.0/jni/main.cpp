#include <jni.h>
#include <dlfcn.h>
#include <string.h>
#include "android_runtime/AndroidRuntime.h"
#include "common.h"
#include "AppBehaviorCapturer/Utils/JavaMethodHooker.h"
#include "AppBehaviorCapturer/System/ApiHookerManager.h"

extern "C" void injectInterface(char*arg){
	LOGD("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	LOGD("*-*-*-*-*-* Injected so *-*-*-*-*-*-*-*");
	LOGD("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
	//获取ApiHookerManager的实例，ApiHookerManager采用单例模式
	ApiHookerManager* apiHookerManager = ApiHookerManager::getInstance();
	//完成系统的初始化
	apiHookerManager->init();
}
