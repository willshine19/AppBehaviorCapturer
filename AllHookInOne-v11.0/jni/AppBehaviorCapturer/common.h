/*
 * common.h
 *
 *  Created on: 2014年9月18日
 *      Author: boyliang
 */

#ifndef COMMON_H_
#define COMMON_H_

//#include <cutils/log.h>
#include <stdlib.h>

#include <jni.h>
#include <stddef.h>
#include <elf.h>
#include "object.h"
#include <android/log.h>
#include <string>

#ifndef LOG_TAG
#define LOG_TAG "AppBehaviorCapturer"
#endif

#define ENABLE_LOG 1
#if ENABLE_LOG
#define LOGW(...) ((void) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#define LOGD(...) ((void) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#define LOGI(...) ((void) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#else
#define LOGE(format, args...) while(0){}
#define LOGD(format, args...) while(0){}
#define LOGI(format, args...) while(0){}
#endif

//用于测试
//ARY_NUMBER需要大于等于CESHI_NUMBER
#define ARY_NUMBER 200
#define CESHI_NUMBER 100

struct HookInfo {
	const char *classDesc;
	const char *methodName;
	const char *methodSig;
	bool isStaticMethod;

	void *originalMethod;
	void *returnType;
	void *paramTypes;
};

#define CHECK_VALID(V) 				\
	if(V == NULL){					\
		LOGE("%s is null.", #V);	\
		exit(-1);					\
	}else{							\
		LOGI("%s is %p.", #V, V);	\
	}								\

#endif /* COMMON_H_ */
