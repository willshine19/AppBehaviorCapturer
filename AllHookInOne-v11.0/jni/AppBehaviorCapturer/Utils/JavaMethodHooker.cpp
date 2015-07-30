/*
 * JavaMethoidHook.cpp
 *
 *  Created on: 2015-4-28
 *      Author: long
 */

#include "JavaMethodHooker.h"
JavaMethodHooker::JavaMethodHooker() {
	// TODO Auto-generated constructor stub

}

JavaMethodHooker::~JavaMethodHooker() {
	// TODO Auto-generated destructor stub
}

bool JavaMethodHooker::isArt(){
	return false;
}
int JavaMethodHooker::hookJavaMethod(JNIEnv* env, ApiHooker* temp,HookInfo *info){
	if (!isArt()) {
		LOGD("begin==================== replace java method in dalvik virtual machine");
		return dalvikJavaMethodHook(env, temp,info);
	} /*else {
		return DalvikMethodHook::art_java_method_hook(env, info);
	}*/
	return 0;
}
int JavaMethodHooker::get(){
	LOGD("succeed-----------------------------");
	return 0;
}
