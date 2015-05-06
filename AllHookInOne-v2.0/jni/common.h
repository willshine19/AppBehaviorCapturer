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
#define LOG_TAG "AndroidSecuritySystem"
#endif

struct HookInfo {
	char *classDesc;
	char *methodName;
	char *methodSig;
	bool isStaticMethod;

	void *originalMethod;
	void *returnType;
	void *paramTypes;
};

#define ENABLE_LOG 1
#if ENABLE_LOG
#define LOGW(...)((void) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#define LOGD(...) ((void) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#define LOGI(...) ((void) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#else
#define LOGE(format, args...)
#define LOGD(format, args...)
#define LOGI(format, args...)
#endif



#define CHECK_VALID(V) 				\
	if(V == NULL){					\
		LOGE("%s is null.", #V);	\
		exit(-1);					\
	}else{							\
		LOGI("%s is %p.", #V, V);	\
	}								\

#endif /* COMMON_H_ */
