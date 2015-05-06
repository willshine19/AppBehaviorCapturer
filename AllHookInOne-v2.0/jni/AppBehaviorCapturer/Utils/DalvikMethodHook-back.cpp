/*
#include "DalvikMethodHook.h"

using android::AndroidRuntime;

#ifdef DEBUG
#define STATIC
#else
#define STATIC static
#endif







static bool g_bAttatedT;
static JavaVM *g_JavaVM;
//HookInfo save;
void DalvikMethodHook::init() {
	g_bAttatedT = false;
	//获取JavaVM，由此可获取JNIEnv
	g_JavaVM = android::AndroidRuntime::getJavaVM();
	LOGD("-------------Init succeed--------------\n");
}


int DalvikMethodHook::calcMethodArgsSize(const char* shorty) {
	int count = 0;
	 Skip the return type.
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

u4 DalvikMethodHook::dvmPlatformInvokeHints(const char* shorty) {
	const char* sig = shorty;
	int padFlags, jniHints;
	char sigByte;
	int stackOffset, padMask;

	stackOffset = padFlags = 0;
	padMask = 0x00000001;

	 Skip past the return type
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
		 too big for "fast" version
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

int DalvikMethodHook::dvmComputeJniArgInfo(const char* shorty) {
	const char* sig = shorty;
	int returnType, jniArgInfo;
	u4 hints;

	 The first shorty character is the return type.
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

jclass DalvikMethodHook::dvmFindJNIClass(JNIEnv *env, const char *classDesc) {
	jclass classObj = env->FindClass(classDesc);

	if (env->ExceptionCheck() == JNI_TRUE) {
		env->ExceptionClear();
	}

	if (classObj == NULL) {
		LOGD("classObj==NULL!!!");
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

ClassObject* DalvikMethodHook::dvmFindClass(const char *classDesc) {
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

ArrayObject* DalvikMethodHook::dvmBoxMethodArgs(const Method* method, const u4* args) {
	LOGD("0");
	const char* desc = &method->shorty[1]; // [0] is the return type.
	LOGD("1.method->shorty[1]=%s", method->shorty);
	
	 count args
	size_t argCount = dexProtoGetParameterCount(&method->prototype);
	LOGD("2.argCount=%d,%s", argCount, argCount);
	STATIC ClassObject* java_lang_object_array = dvmFindSystemClass(
			"[Ljava/lang/Object;");
	LOGD("3");
	
	 allocate storage
	ArrayObject* argArray = dvmAllocArrayByClass(java_lang_object_array,
			argCount, ALLOC_DEFAULT);
	LOGD("4");
	if (argArray == NULL)
		return NULL;
	LOGD("5");
	Object** argObjects = (Object**) (void*) argArray->contents;
	LOGD("6");

	 * Fill in the array.

	size_t srcIndex = 0;
	size_t dstIndex = 0;
	while (*desc != '\0') {
		char descChar = *(desc++);
		JValue value;

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
			 argObjects is tracked, don't need to hold this too
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
	LOGD("end!");
	return argArray;
}

ArrayObject* DalvikMethodHook::dvmGetMethodParamTypes(const Method* method,
		const char* methodsig) {
	 count args
	size_t argCount = dexProtoGetParameterCount(&method->prototype);
	STATIC ClassObject* java_lang_object_array = dvmFindSystemClass(
			"[Ljava/lang/Object;");

	 allocate storage
	ArrayObject* argTypes = dvmAllocArrayByClass(java_lang_object_array,
			argCount, ALLOC_DEFAULT);
	if (argTypes == NULL) {
		return NULL;
	}

	Object** argObjects = (Object**) argTypes->contents;
	const char *desc = (const char *) (strchr(methodsig, '(') + 1);


	 * Fill in the array.

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

			desc_index++;
			break;

		case '[':
			isArray = true;
			desc_index++;
			break;

		case 'L':
			int s_pos = desc_index, e_pos = desc_index;
			while (desc[++e_pos] != ';')
				;
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

void DalvikMethodHook::method_handler(const u4* args, JValue* pResult,
		const Method* method, struct Thread* self) {
	LOGD("method_handler----------------start------------------");
	LOGD("save.classDesc=%s,%x", save.classDesc, save.classDesc);
	LOGD("save.methodName=%s,%x", save.methodName, save.methodName);
	LOGD("save.methodSig=%s,%x", save.methodSig, save.methodSig);
	LOGD("save.isStaticMethod=%s,%x", save.isStaticMethod, save.isStaticMethod);
	LOGD("save.originalMethod=%s,%x", save.originalMethod, save.originalMethod);
	LOGD("save.paramTypes=%s,%x", save.paramTypes, save.paramTypes);
	LOGD("save.returnType=%s,%x", save.returnType, save.returnType);
//	LOGD("args[0]=%x,%s",args[0],args[0]);
//	LOGD("args[1]=%x,%s",args[1],args[1]);
//	LOGD("args[2]=%x,%s",args[2],args[2]);
//	LOGD("args[3]=%x,%s",args[3],args[3]);
//	LOGD("args[4]=%x,%s",args[4],args[4]);
//	LOGD("JValue=%x,%s",pResult,pResult);
//	LOGD("Method=%x,%s",method,method);

//	HookInfo* info = (HookInfo*)method->insns;
	HookInfo* info = &save;
	
//	LOGI("entry %s->%s", info->classDesc, info->methodName);
	LOGD("info->classDesc=%s,%x", info->classDesc, info->classDesc);
	LOGD("info->methodName=%s,%x", info->methodName, info->methodName);
	LOGD("info->methodSig=%s,%x", info->methodSig, info->methodSig);
	LOGD("info->isStaticMethod=%s,%x", info->isStaticMethod, info->isStaticMethod);
	LOGD("info->originalMethod=%s,%x", info->originalMethod, info->originalMethod);
	LOGD("info->paramTypes=%s,%x", info->paramTypes, info->paramTypes);
	LOGD("info->returnType=%s,%x", info->returnType, info->returnType);
//	LOGD("info->classDesc=%s",info->classDesc);
//	LOGD("info->methodName=%s",info->methodName);
//	LOGD("info->methodSig=%s",info->methodSig);
//	LOGD("info->isStaticMethod=%s",info->isStaticMethod);
	
	LOGD("method_handler----------------step 1------------------");
	Method* originalMethod = reinterpret_cast<Method*>(info->originalMethod);
	Object* thisObject = !info->isStaticMethod ? (Object*) args[0] : NULL;
	
	LOGD("method_handler----------------step 2------------------");
	const char* desc = originalMethod->shorty;
	ArrayObject* argTypes = dvmBoxMethodArgs(originalMethod,
			info->isStaticMethod ? args : args + 1);
	
	LOGD("%s-----------------------step 2.5--------------------", desc);
	pResult->l = (void *) dvmInvokeMethod(thisObject, originalMethod, argTypes,
			(ArrayObject *) info->paramTypes, (ClassObject *) info->returnType,
			true);
	
	LOGD("method_handler----------------step 3------------------");
	dvmReleaseTrackedAlloc((Object *) argTypes, self);
	
	LOGD("method_handler----------------end------------------");
}

extern int __attribute__ ((visibility ("hidden"))) dalvik_java_method_hook(
		JNIEnv* env, HookInfo *info) {
	
	//__attribute__ ((visibility("hidden")))，可以用于抑制将一个函数的名称被导出，对连接该库的程序文件来说，该函数是不可见的
	LOGD("-----------entry dalvik_java_method_hook------------");
	const char* classDesc = info->classDesc; //类描述
	LOGD("info->classDesc=%s", info->classDesc);
	const char* methodName = info->methodName; //方法名
	LOGD("info->methodName=%s", info->methodName);
	const char* methodSig = info->methodSig; //方法签名
	LOGD("info->methodSig=%s", info->methodSig);
	const bool isStaticMethod = info->isStaticMethod; //是否为静态方法
	LOGD("info->isStaticMethod=%s", info->isStaticMethod);
	LOGD("isStaticMethod=%d", isStaticMethod);

	jclass classObj = DalvikMethodHook::dvmFindJNIClass(env, classDesc); //寻找到这个类，返回它新的global reference
	if (classObj == NULL) {
		LOGE("[-] %s class not found", classDesc);
		return -1;
	}
	LOGD("dalvik_java_method_hook-------------------Class %s has found", classDesc);

	//jmethodID类表示Java端的属性和方法
	jmethodID methodId =isStaticMethod ?
					env->GetStaticMethodID(classObj, methodName, methodSig) :
					env->GetMethodID(classObj, methodName, methodSig);

	if (methodId == NULL) {
		LOGE("[-] %s->%s method not found", classDesc, methodName);
		return -1;
	}
	LOGD(
			"dalvik_java_method_hook-------------------MethodId %s has found in %s", methodName, classDesc);

	// backup method
	Method* method = (Method*) methodId;
	if (method->nativeFunc == &DalvikMethodHook::method_handler){ //判断是否已经被hook
		LOGW("[*] %s->%s method had been hooked", classDesc, methodName);
		return -1;
	}
	//如果没有被hook,开始暂存
	Method* bakMethod = (Method*) malloc(sizeof(Method));
	memcpy(bakMethod, method, sizeof(Method));
	LOGD("dalvik_java_method_hook-------------------save method success");

	// init info
	info->originalMethod = (void *) bakMethod;
	LOGD("info->originalMethod=%s", info->originalMethod);
	info->returnType = (void *) dvmGetBoxedReturnType(bakMethod);
	LOGD("info->returnType=%s", info->returnType);
	info->paramTypes = dvmGetMethodParamTypes(bakMethod, info->methodSig);
	LOGD("info->paramTypes=%s", info->paramTypes);

	
	// ***hook method***
	LOGD("dalvik_java_method_hook----------hook method start");
	//这一步应该是获取参数的个数
	int argsSize = calcMethodArgsSize(method->shorty);
	LOGD("argsSize=%d", argsSize);
	if (!dvmIsStaticMethod(method))
		argsSize++;
	LOGD("argsSize=%d", argsSize);
	// 在做什么
	SET_METHOD_FLAG(method, ACC_NATIVE);
	method->registersSize = method->insSize = argsSize;
	method->outsSize = 0;
	method->jniArgInfo = dvmComputeJniArgInfo(method->shorty);
	LOGD("method->jniArgInfo=%s", method->jniArgInfo);
	//不知道这是什么
	LOGD("method->shorty=%s", method->shorty);
	//第一个hook中shorty=LIL(String, int, String)，shorty[0]是返回的类型
	LOGD("dalvik_java_method_hook-----------hook method success");


//	HookInfo* info1 = (HookInfo*)method->insns;
	LOGD("ok");
	LOGD("info->classDesc=%s,%x", info->classDesc, info->classDesc);
	LOGD("info->methodName=%s,%x", info->methodName, info->methodName);
	LOGD("info->methodSig=%s,%x", info->methodSig, info->methodSig);
	LOGD("info->isStaticMethod=%s,%x", info->isStaticMethod, info->isStaticMethod);
	LOGD("info->originalMethod=%s,%x", info->originalMethod, info->originalMethod);
	LOGD("info->paramTypes=%s,%x", info->paramTypes, info->paramTypes);
	LOGD("info->returnType=%s,%x", info->returnType, info->returnType);
	// save info to insns
	method->insns = (u2*)info;
	2015-3-28
	 * sun
	 * 若通过注入的方式加载动态链接库，则无法利用method->insns暂存结构体指针来保存
	 * info的信息。调试过程发现，注入后，method->insns的指针指不会改变，但所指向
	 * 的内容已经不再是原内容了，classDesc为乱码，显而易见的是methodName（Thread.start）
	 * 也由原来的start变成了Ljava/lang/Runnable。
	 * 曾尝试在该文件中加入个全局指针变量HookInfo* save来保存info 的指针，但结果和将info
	 * 指针存入method->insns的效果一样。
	 * 然后尝试将该全局变量指针改为结构体，声明HookInfor save，不通过指针来保存，然后在函数
	 * 调用中通过Hookinfo* info = &save来获取保存的函数信息。此方法可行，但显然空间开销骤增


	save.classDesc = info->classDesc;
	save.isStaticMethod = info->isStaticMethod;
	save.methodName = info->methodName;
	save.methodSig = info->methodSig;
	save.originalMethod = info->originalMethod;
	save.paramTypes = info->paramTypes;
	save.returnType = info->returnType;

	// bind the bridge func，only one line
	method->nativeFunc = &DalvikMethodHook::method_handler;
	LOGI("[+] %s->%s was hooked\n", classDesc, methodName);

	return 0;
}
*/
