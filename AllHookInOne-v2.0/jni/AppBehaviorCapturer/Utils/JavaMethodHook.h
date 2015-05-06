/*
 * JavaMethoidHook.h
 *
 *  Created on: 2015-4-28
 *      Author: long
 */

#ifndef JAVAMETHODHOOK_H_
#define JAVAMETHODHOOK_H_

#include <jni.h>
#include <stddef.h>
#include <elf.h>
#include "object.h"
#include "common.h"
#include "DalvikMethodHook.h"

class JavaMethodHook {
public:
	JavaMethodHook();
	virtual ~JavaMethodHook();
	bool isArt();
	int hookJavaMethod(JNIEnv* env, HookInfo *info);
	int get();
};

#endif /* JAVAMETHOIDHOOK_H_ */
