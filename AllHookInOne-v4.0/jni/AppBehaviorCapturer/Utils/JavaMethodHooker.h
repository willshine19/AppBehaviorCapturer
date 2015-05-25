/*
 * JavaMethoidHook.h
 *
 *  Created on: 2015-4-28
 *      Author: long
 */

#ifndef JAVAMETHODHOOKER_H_
#define JAVAMETHODHOOKER_H_

#include <jni.h>
#include <stddef.h>
#include <elf.h>
#include "object.h"
#include "common.h"
#include "DalvikMethodHooker.h"


class JavaMethodHooker {
public:
	JavaMethodHooker();
	virtual ~JavaMethodHooker();
	bool isArt();
	int hookJavaMethod(JNIEnv* env, ApiHooker* temp,HookInfo *info);
	int get();
};

#endif /* JAVAMETHOIDHOOK_H_ */
