/*
 * JavaMethoidHook.cpp
 *
 *  Created on: 2015-4-28
 *      Author: long
 */

#include "JavaMethodHook.h"
JavaMethodHook::JavaMethodHook() {
	// TODO Auto-generated constructor stub

}

JavaMethodHook::~JavaMethodHook() {
	// TODO Auto-generated destructor stub
}

bool JavaMethodHook::isArt(){
	return false;
}
int JavaMethodHook::hookJavaMethod(JNIEnv* env, HookInfo *info){
	if (!isArt()) {
		LOGD("begin==================== replace java method in dalvik virtual machine");
		return dalvik_java_method_hook(env, info);
	} /*else {
		return DalvikMethodHook::art_java_method_hook(env, info);
	}*/
	return 0;
}
int JavaMethodHook::get(){
	LOGD("succeed-----------------------------");
	return 0;
}
