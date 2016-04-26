#include "DalvikMethodHooker.h"

using android::AndroidRuntime;
using namespace __gnu_cxx;

/**
 * 从方法签名中，解析除java方法的输入参数的个数
 * @param shorty: short-form method descriptor string 字符串 函数签名的简写
 * @return 输入参数的个数
 */
int calcMethodArgsSize(const char* shorty) {
	int count = 0;

	/* Skip the return type. */
	shorty++;

	for (;;) {
		switch (*(shorty++)) {
		case '\0': {
			return count;
		}
		case 'D':
		case 'J': {
			count += 2;
			break;
		}
		default: {
			count++;
			break;
		}
		}
	}
	return count;
}

u4 dvmPlatformInvokeHints(const char* shorty) {
	const char* sig = shorty;
	int padFlags, jniHints;
	char sigByte;
	int stackOffset, padMask;

	stackOffset = padFlags = 0;
	padMask = 0x00000001;

	/* Skip past the return type */
	sig++;

	while (true) {
		sigByte = *(sig++);

		if (sigByte == '\0')
			break;

		if (sigByte == 'D' || sigByte == 'J') {
			if ((stackOffset & 1) != 0) {
				padFlags |= padMask;
				stackOffset++;
				padMask <<= 1;
			}
			stackOffset += 2;
			padMask <<= 2;
		} else {
			stackOffset++;
			padMask <<= 1;
		}
	}

	jniHints = 0;

	if (stackOffset > DALVIK_JNI_COUNT_SHIFT) {
		/* too big for "fast" version */
		jniHints = DALVIK_JNI_NO_ARG_INFO;
	} else {
		assert((padFlags & (0xffffffff << DALVIK_JNI_COUNT_SHIFT)) == 0);
		stackOffset -= 2; // r2/r3 holds first two items
		if (stackOffset < 0)
			stackOffset = 0;
		jniHints |= ((stackOffset + 1) / 2) << DALVIK_JNI_COUNT_SHIFT;
		jniHints |= padFlags;
	}

	return jniHints;
}

/**
 *
 * @param shorty 函数签名的简写
 * @return 装入method->jniArgInfo
 */
int dvmComputeJniArgInfo(const char* shorty) {
	const char* sig = shorty;
	int returnType, jniArgInfo;
	u4 hints;

	/* The first shorty character is the return type. */
	switch (*(sig++)) {
	case 'V':
		returnType = DALVIK_JNI_RETURN_VOID;
		break;
	case 'F':
		returnType = DALVIK_JNI_RETURN_FLOAT;
		break;
	case 'D':
		returnType = DALVIK_JNI_RETURN_DOUBLE;
		break;
	case 'J':
		returnType = DALVIK_JNI_RETURN_S8;
		break;
	case 'Z':
	case 'B':
		returnType = DALVIK_JNI_RETURN_S1;
		break;
	case 'C':
		returnType = DALVIK_JNI_RETURN_U2;
		break;
	case 'S':
		returnType = DALVIK_JNI_RETURN_S2;
		break;
	default:
		returnType = DALVIK_JNI_RETURN_S4;
		break;
	}

	jniArgInfo = returnType << DALVIK_JNI_RETURN_SHIFT;

	hints = dvmPlatformInvokeHints(shorty);

	if (hints & DALVIK_JNI_NO_ARG_INFO) {
		jniArgInfo |= DALVIK_JNI_NO_ARG_INFO;
	} else {
		assert((hints & DALVIK_JNI_RETURN_MASK) == 0);
		jniArgInfo |= hints;
	}

	return jniArgInfo;
}

/**
 * 通过类名 返回 这个java类
 * @param classDesc 类名
 * @return java类在jni层的对应的变量表示
 */
jclass dvmFindJNIClass(JNIEnv *env, const char *classDesc) {
	jclass classObj = env->FindClass(classDesc);

	if (env->ExceptionCheck() == JNI_TRUE) {
		env->ExceptionClear();
	}

	if (classObj == NULL) {
		//一般不应该执行到这里
		jclass clazzApplicationLoaders = env->FindClass(
				"android/app/ApplicationLoaders");
		CHECK_VALID(clazzApplicationLoaders);

		jfieldID fieldApplicationLoaders = env->GetStaticFieldID(
				clazzApplicationLoaders, "gApplicationLoaders",
				"Landroid/app/ApplicationLoaders;");
		CHECK_VALID(fieldApplicationLoaders);

		jobject objApplicationLoaders = env->GetStaticObjectField(
				clazzApplicationLoaders, fieldApplicationLoaders);
		CHECK_VALID(objApplicationLoaders);

		jfieldID fieldLoaders = env->GetFieldID(clazzApplicationLoaders,
				"mLoaders", "Ljava/util/Map;");
		CHECK_VALID(fieldLoaders);

		jobject objLoaders = env->GetObjectField(objApplicationLoaders,
				fieldLoaders);
		CHECK_VALID(objLoaders);

		jclass clazzHashMap = env->GetObjectClass(objLoaders);
		static jmethodID methodValues = env->GetMethodID(clazzHashMap, "values",
				"()Ljava/util/Collection;");
		jobject values = env->CallObjectMethod(objLoaders, methodValues);
		jclass clazzValues = env->GetObjectClass(values);
		static jmethodID methodToArray = env->GetMethodID(clazzValues,
				"toArray", "()[Ljava/lang/Object;");
		jobjectArray classLoaders = (jobjectArray) env->CallObjectMethod(values,
				methodToArray);

		int size = env->GetArrayLength(classLoaders);
		jstring param = env->NewStringUTF(classDesc);

		for (int i = 0; i < size; i++) {
			jobject classLoader = env->GetObjectArrayElement(classLoaders, i);
			jclass clazzCL = env->GetObjectClass(classLoader);
			static jmethodID loadClass = env->GetMethodID(clazzCL, "loadClass",
					"(Ljava/lang/String;)Ljava/lang/Class;");
			classObj = (jclass) env->CallObjectMethod(classLoader, loadClass,
					param);

			if (classObj != NULL) {
				break;
			}
		}
	}
	//Global Reference 全局引用 ，这种对象如不主动释放，它永远都不会被垃圾回收
	return (jclass) env->NewGlobalRef(classObj);
}

/**
 *
 *
 */
ClassObject* dvmFindClass(const char *classDesc) {
	JNIEnv *env = AndroidRuntime::getJNIEnv();
	assert(env != NULL);

	char *newclassDesc = dvmDescriptorToName(classDesc);

	jclass jnicls = dvmFindJNIClass(env, newclassDesc);
	ClassObject *res =
			jnicls ?
					static_cast<ClassObject*>(dvmDecodeIndirectRef(
							dvmThreadSelf(), jnicls)) :
					NULL;
	env->DeleteGlobalRef(jnicls);
	free(newclassDesc);
	return res;
}

/**
 *
 *
 */
ArrayObject* dvmBoxMethodArgs(const Method* method, const u4* args) {
	LOGD("[w]1.5.1");
	const char* desc = &method->shorty[1]; // [0] is the return type.
	LOGD("[w]1.5.2");
	/* count args */
	size_t argCount = dexProtoGetParameterCount(&method->prototype);
	LOGD("[w]1.5.3");
	ClassObject* java_lang_object_array = dvmFindSystemClass(
			"[Ljava/lang/Object;");
	LOGD("[w]1.5.4");
	/* allocate storage */
	ArrayObject* argArray = dvmAllocArrayByClass(java_lang_object_array,
			argCount, ALLOC_DEFAULT);
	LOGD("[w]1.5.5");
	if (argArray == NULL)
		return NULL;
	Object** argObjects = (Object**) (void*) argArray->contents;
	LOGD("[w]1.5.6");
	// Fill in the array.
	size_t srcIndex = 0;
	size_t dstIndex = 0;
	while (*desc != '\0') {
		char descChar = *(desc++);
		JValue value;
		LOGD("[w]1.5.7while");
		switch (descChar) {
		case 'Z':
		case 'C':
		case 'F':
		case 'B':
		case 'S':
		case 'I':
			value.i = args[srcIndex++];
			argObjects[dstIndex] = (Object*) dvmBoxPrimitive(value,
					dvmFindPrimitiveClass(descChar));
			/* argObjects is tracked, don't need to hold this too */
			dvmReleaseTrackedAlloc(argObjects[dstIndex], NULL);
			dstIndex++;
			break;
		case 'D':
		case 'J':
			value.j = dvmGetArgLong(args, srcIndex);
			srcIndex += 2;
			argObjects[dstIndex] = (Object*) dvmBoxPrimitive(value,
					dvmFindPrimitiveClass(descChar));
			dvmReleaseTrackedAlloc(argObjects[dstIndex], NULL);
			dstIndex++;
			break;
		case '[':
		case 'L':
			argObjects[dstIndex++] = (Object*) args[srcIndex++];
			break;
		}
	}
	LOGD("[w]1.5.8");
	return argArray;
}

/**
 * 该方法非虚拟机源码，返回值ArrayObject*，用于dvmInvokeMethod函数（虚拟机源码），如下
 * Object* dvmInvokeMethod(Object* obj, const Method* method, ArrayObject* argList, ArrayObject* params, ClassObject* returnType, bool noAccessCheck)
 * 就是用于其中的参数params
 */
ArrayObject* dvmGetMethodParamTypes(const Method* method,
		const char* methodsig) {
	/* count args */
	size_t argCount = dexProtoGetParameterCount(&method->prototype);
	ClassObject* java_lang_object_array = dvmFindSystemClass(
			"[Ljava/lang/Object;");
	/* allocate storage */
	ArrayObject* argTypes = dvmAllocArrayByClass(java_lang_object_array,
			argCount, ALLOC_DEFAULT);
	if (argTypes == NULL) {
		return NULL;
	}
	Object** argObjects = (Object**) argTypes->contents;
	const char *desc = (const char *) (strchr(methodsig, '(') + 1);

	/*
	 * Fill in the array.
	 */
	size_t desc_index = 0;
	size_t arg_index = 0;
	bool isArray = false;
	char descChar = desc[desc_index];
	while (descChar != ')') {
		switch (descChar) {
		case 'Z':
		case 'C':
		case 'F':
		case 'B':
		case 'S':
		case 'I':
		case 'D':
		case 'J':
			if (!isArray) {
				argObjects[arg_index++] = dvmFindPrimitiveClass(descChar);
				isArray = false;
			} else {
				char buf[3] = { 0 };
				memcpy(buf, desc + desc_index - 1, 2);
				argObjects[arg_index++] = dvmFindSystemClass(buf);
			}
			//add by lwl
			isArray = false;
			desc_index++;
			break;
		case '[':
			isArray = true;
			desc_index++;
			break;
		case 'L':
			int s_pos = desc_index, e_pos = desc_index;
			while (desc[++e_pos] != ';')
				; //什么意思？
			s_pos = isArray ? s_pos - 1 : s_pos;
			isArray = false;

			size_t len = e_pos - s_pos + 1;
			char buf[128] = { 0 };
			memcpy((void *) buf, (const void *) (desc + s_pos), len);
			argObjects[arg_index++] = dvmFindClass(buf);
			desc_index = e_pos + 1;
			break;
		}
		descChar = desc[desc_index];
	}
	return argTypes;
}

/**
 * 该函数以函数指针的形式被赋给了 method->nativeFunc
 * method->nativeFunc = methodHandler
 * 当java层调用目标方法时，若该方法已被hook，则调用相应的methodHandler函数
 * @param args： 一个整数数组
 */
void methodHandler(const u4* args, JValue* pResult, const Method* method,
		struct Thread* self) {
	//时间测试，记录处理Api的start时间，即t1
//	TimeUtils* timeUtils = TimeUtils::getInstance();
//	timeUtils->setT1StartTime();

	// 在哈希表中查找该方法
	const char* temp = method->name;
	LOGD("[w]0 method_handler of %s----------------begin------------------",
			temp);
	//获取ApiHookerManager中的mApiHookerHashMap中的对应temp的键值对
	auto iElementFound =
			ApiHookerManager::getInstance()->mApiHookerHashMap.find(temp);
	if (iElementFound
			!= ApiHookerManager::getInstance()->mApiHookerHashMap.end()) {
//		LOGD("find %s in mApiHookerHashMap", temp);
	} else {
		char* tmp = (char*) malloc(
				strlen(method->name) + strlen(method->clazz->descriptor) + 1);
		strcpy(tmp, method->name);
		strcat(tmp, method->clazz->descriptor);
		iElementFound = ApiHookerManager::getInstance()->mApiHookerHashMap.find(
				tmp);
		if (iElementFound
				!= ApiHookerManager::getInstance()->mApiHookerHashMap.end()) {
//			LOGD("find %s in mApiHookerHashMap", tmp);
			free(tmp);
		} else {
			LOGE("can not find %s in mApiHookerHashMap!", temp);
			return;
		}
	}
	LOGD("[w]1");
	ApiHooker* tempApiHooker = iElementFound->second;
	//	LOGD("调用ApiHooker的main()函数;");
//	tempApiHooker->main(args);
	//取出对应ApiHooker中保存的HookInfo结构体，内部保存的是对应temp API的信息
	LOGD("[w]1.1");
	HookInfo* info = &(iElementFound->second->save);
	LOGD("[w]1.2");
	Method* originalMethod = reinterpret_cast<Method*>(info->originalMethod); //强转
	LOGD("[w]1.3");
	Object* thisObject = !info->isStaticMethod ? (Object*) args[0] : NULL; //输入参数
	LOGD("[w]1.4");
	const char* desc = originalMethod->shorty; //方法介绍
	LOGD("[w]1.5");
	ArrayObject* argTypes = dvmBoxMethodArgs(originalMethod,
			info->isStaticMethod ? args : args + 1); //返回参数个数
	LOGD("[w]1.6");
	// 关键：调用原方法
	Object* result = dvmInvokeMethod(thisObject, originalMethod, argTypes,
			(ArrayObject *) info->paramTypes, (ClassObject *) info->returnType,
			true); //obj是this或者null（如果是static方法），method可以直接使用hook之前copy的对象
	LOGD("[w]1.7");
	pResult->l = (void*) result;
	LOGD("[w]2");
	if (tempApiHooker->main(args)) {
		LOGD("[w]3");
		if(tempApiHooker->parseResult(result)){ //解析返回参数
			LOGD("[w]4");
			tempApiHooker->collectBaseInfo(); //将获取信息存到发送队列
		}

	}
	LOGD("[w]5");
	dvmReleaseTrackedAlloc((Object *) argTypes, self); //释放内存
	LOGD("[w]6 method_handler of %s----------------end------------------",
			temp);
}

/**
 * hook一个指定的java层的api的核心逻辑
 * 该cpp文件的入口
 * @param env 指向JNI环境
 * @param temp 指向ApiHooker实例
 * @param info 指向HookInfo结构体，内含被hook的java method的信息
 */
int dalvikJavaMethodHook(JNIEnv* env, ApiHooker* temp, HookInfo *info) {

	// step 1
	const char* classDesc = info->classDesc; //类描述
	const char* methodName = info->methodName; //方法名
	const char* methodSig = info->methodSig; //方法签名
	const bool isStaticMethod = info->isStaticMethod; //是否为静态方法

	// step 2 寻找到目标类，返回它新的global reference
	jclass classObj = dvmFindJNIClass(env, classDesc);
	if (classObj == NULL) {
		LOGE("[-] dalvikJavaMethodHook: %s class was not found", classDesc);
		return -1;
	}
	LOGD("-------------------Class %s has found", classDesc);

	// step 3 返回目标方法的标示
	//jmethodID类表示Java端的属性和方法
	jmethodID methodId =
			isStaticMethod ?
					env->GetStaticMethodID(classObj, methodName, methodSig) :
					env->GetMethodID(classObj, methodName, methodSig);
	if (methodId == NULL) {
		LOGE("[-] %s->%s method not found", classDesc, methodName);
		return -1;
	}
	LOGD("-------------------MethodId %s has found in %s", methodName,
			classDesc);

	// step 4 判断该方法是否已经被hook过
	Method* method = (Method*) methodId;
	if (method->nativeFunc == methodHandler) {
		LOGW("[*] %s->%s method had been hooked", classDesc, methodName);
		// 该方法已经被hook过了
		return -1;
	}

	// step 5 如果没有被hook,备份Method结构体
	Method* bakMethod = (Method*) malloc(sizeof(Method)); // 原方法，向系统申请分配指定size个字节的内存空间
	memcpy(bakMethod, method, sizeof(Method));
	LOGD("dalvik_java_method_hook-------------------save method success");

	// step 6 填充 info
	info->originalMethod = (void *) bakMethod;
//	LOGD("info->originalMethod=%s", (char*)info->originalMethod);
	info->returnType = (void *) dvmGetBoxedReturnType(bakMethod);
//	LOGD("info->returnType=%s", (char*)info->returnType);
	info->paramTypes = dvmGetMethodParamTypes(bakMethod, info->methodSig);
//	LOGD("info->paramTypes=%s", (char*)info->paramTypes);

	// step 7 hook
	//这一步应该是获取参数的个数
	int argsSize = calcMethodArgsSize(method->shorty);
	LOGD("dalvikJavaMethodHook:method->shorty = %s", method->shorty);
	LOGD("dalvikJavaMethodHook:argsSize = %d", argsSize);
	if (!dvmIsStaticMethod(method))
		argsSize++;
	LOGD("argsSize=%d", argsSize);

	// step 8 修改 method结构体
	SET_METHOD_FLAG(method, ACC_NATIVE);
	// 修改 method->accessFlags 为 ACC_NATIVE
	method->registersSize = method->insSize = argsSize;
	method->outsSize = 0;
	method->jniArgInfo = dvmComputeJniArgInfo(method->shorty);
	method->nativeFunc = methodHandler; //关键 替换函数指针
	//在某些ApiHooker的hook过程中，注入过程很有可能卡在argsSize = XXX，经验证与下面的这条log输出有关系，注释掉即可
	//	LOGD("method->jniArgInfo=%d", method->jniArgInfo);
	//	LOGD("method->shorty=%s", method->shorty);
	//第一个hook中shorty=LIL(String, int, String)，shorty[0]是返回的类型

	// step 9 save info into ApiHooker save结构体中
	temp->save.classDesc = info->classDesc;
	temp->save.isStaticMethod = info->isStaticMethod;
	temp->save.methodName = info->methodName;
	temp->save.methodSig = info->methodSig;
	temp->save.originalMethod = info->originalMethod;
	temp->save.paramTypes = info->paramTypes;
	temp->save.returnType = info->returnType;

	LOGI("[+] %s->%s was hooked successfully.\n", classDesc, methodName);

	return 0;
}
