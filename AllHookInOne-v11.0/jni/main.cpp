#include <jni.h>
#include <dlfcn.h>
#include <string.h>
#include "android_runtime/AndroidRuntime.h"
#include "common.h"
#include "AppBehaviorCapturer/Utils/JavaMethodHooker.h"
#include "AppBehaviorCapturer/System/ApiHookerManager.h"


/**
 * 注入程序直接启动so库中的injectInterface函数,该函数是so库的唯一入口
 */
extern "C" void injectInterface(char* arg){
	LOGD("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
	LOGD("*-*-*-*-*-* Injected so *-*-*-*-*-*-*-*");
	LOGD("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
	//获取ApiHookerManager的实例，ApiHookerManager采用单例模式
	ApiHookerManager* apiHookerManager = ApiHookerManager::getInstance();
	//完成系统的初始化
	apiHookerManager->main();
	LOGD("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
	LOGD("*-*-*-*-*- Injected so End -*-*-*-*-*-*");
	LOGD("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
}
