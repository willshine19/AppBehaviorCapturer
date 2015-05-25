#include "DalvikMethodHooker.h"

using android::AndroidRuntime;
using namespace __gnu_cxx;

HookInfo save;

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

 jclass dvmFindJNIClass(JNIEnv *env, const char *classDesc) {
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

 ArrayObject* dvmBoxMethodArgs(const Method* method, const u4* args) {
	LOGD("0");
	const char* desc = &method->shorty[1]; // [0] is the return type.
	LOGD("1.method->shorty[1]=%s", method->shorty);

	/* count args */
	size_t argCount = dexProtoGetParameterCount(&method->prototype);
	LOGD("2.argCount=%d", argCount);
	 ClassObject* java_lang_object_array = dvmFindSystemClass(
			"[Ljava/lang/Object;");
	LOGD("3");

	/* allocate storage */
	ArrayObject* argArray = dvmAllocArrayByClass(java_lang_object_array,
			argCount, ALLOC_DEFAULT);
	LOGD("4");
	if (argArray == NULL)
		return NULL;
	LOGD("5");
	Object** argObjects = (Object**) (void*) argArray->contents;
	LOGD("6");
	/*
	 * Fill in the array.
	 */
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
	LOGD("end!");
	return argArray;
}

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
void methodHandler(const char* temp,const u4* args, JValue* pResult,
		const Method* method, struct Thread* self){
	LOGD("method_handler----------------start------------------");
	//获取ApiHookerManager中的mApiHookerHashMap中的对应temp的键值对
	auto iElementFound = ApiHookerManager::getInstance()->mApiHookerHashMap.find(temp);
	if(iElementFound != ApiHookerManager::getInstance()->mApiHookerHashMap.end()){
		LOGD("find %s in mApiHookerHashMap",temp);
	}
	else
		LOGE( "Key has no corresponding value in unordered map!");
	ApiHooker* tempApiHooker = &iElementFound->second ;
	tempApiHooker->main(self->threadId);//传入线程号
/*
 //多态存在问题，还需要解决
	reinterpret_cast<StartThreadApiHooker*>(&iElementFound->second)->parseParameter();
StartThreadApiHooker* tempApiHooker = (StartThreadApiHooker*)&(iElementFound->second);
//调用对应ApiHooker的main方法，进行行为采集与信息保存等工作
((StartThreadApiHooker*)&(iElementFound->second))->parseParameter();
//	tempApiHooker->parseParameter();
*/
	//取出对应ApiHooker中保存的HookInfo结构体，内部保存的是对应temp API 的
	HookInfo* info = &(iElementFound->second.save);
	LOGD("info->classDesc=%s,%x", info->classDesc, info->classDesc);
	LOGD("info->methodName=%s,%x", info->methodName, info->methodName);
	LOGD("info->methodSig=%s,%x", info->methodSig, info->methodSig);
	LOGD("info->isStaticMethod=%s,%x", info->isStaticMethod, info->isStaticMethod);
	LOGD("info->originalMethod=%s,%x", info->originalMethod, info->originalMethod);
	LOGD("info->paramTypes=%s,%x", info->paramTypes, info->paramTypes);
	LOGD("info->returnType=%s,%x", info->returnType, info->returnType);

	Method* originalMethod = reinterpret_cast<Method*>(info->originalMethod);
	Object* thisObject = !info->isStaticMethod ? (Object*) args[0] : NULL;

	const char* desc = originalMethod->shorty;

	ArrayObject* argTypes = dvmBoxMethodArgs(originalMethod,
			info->isStaticMethod ? args : args + 1);

	pResult->l = (void *) dvmInvokeMethod(thisObject, originalMethod, argTypes,
			(ArrayObject *) info->paramTypes, (ClassObject *) info->returnType,
			true);

	dvmReleaseTrackedAlloc((Object *) argTypes, self);

	LOGD("method_handler----------------end------------------");
}
void startMethodHandler(const u4* args, JValue* pResult,
		const Method* method, struct Thread* self) {
	methodHandler("start",args,pResult,method,self);
}
void onCreateMethodHandler(const u4* args, JValue* pResult,
		const Method* method, struct Thread* self){
	methodHandler("onCreate",args,pResult,method,self);
}
void getMacAddressMethodHandler(const u4* args, JValue* pResult,
		const Method* method, struct Thread* self){
	methodHandler("getMacAddress",args,pResult,method,self);
}
int dalvikJavaMethodHook(JNIEnv* env, ApiHooker* temp,HookInfo *info) {

	const char* classDesc = info->classDesc; //类描述
	LOGD("info->classDesc=%s", info->classDesc);
	const char* methodName = info->methodName; //方法名
	LOGD("info->methodName=%s", info->methodName);
	const char* methodSig = info->methodSig; //方法签名
	LOGD("info->methodSig=%s", info->methodSig);
	const bool isStaticMethod = info->isStaticMethod; //是否为静态方法
	LOGD("info->isStaticMethod=%s", info->isStaticMethod);
	LOGD("isStaticMethod=%d", isStaticMethod);

	jclass classObj = dvmFindJNIClass(env, classDesc); //寻找到这个类，返回它新的global reference
	if (classObj == NULL) {
		LOGE("[-] %s class not found", classDesc);
		return -1;
	}
	LOGD("-------------------Class %s has found", classDesc);

	//jmethodID类表示Java端的属性和方法
	jmethodID methodId =isStaticMethod ?
					env->GetStaticMethodID(classObj, methodName, methodSig) :
					env->GetMethodID(classObj, methodName, methodSig);

	if (methodId == NULL) {
		LOGE("[-] %s->%s method not found", classDesc, methodName);
		return -1;
	}
	LOGD("-------------------MethodId %s has found in %s", methodName, classDesc);

	// backup method
	Method* method = (Method*) methodId;
	int apiHookerFlag = temp->getApiFlag();
	switch (apiHookerFlag){
		case(START):
				if(method->nativeFunc == startMethodHandler){
					LOGW("[*] %s->%s method had been hooked", classDesc, methodName);
					return -1;
				}break;
		case(ONCREATE):
				if(method->nativeFunc == onCreateMethodHandler){
					LOGW("[*] %s->%s method had been hooked", classDesc, methodName);
					return -1;
				}break;
		case(GETMACADDRESS):
				if(method->nativeFunc == getMacAddressMethodHandler){
					LOGW("[*] %s->%s method had been hooked", classDesc, methodName);
					return -1;
				}break;
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
	LOGD("info->classDesc=%s,%x", info->classDesc, info->classDesc);
	LOGD("info->methodName=%s,%x", info->methodName, info->methodName);
	LOGD("info->methodSig=%s,%x", info->methodSig, info->methodSig);
	LOGD("info->isStaticMethod=%s,%x", info->isStaticMethod, info->isStaticMethod);
	LOGD("info->originalMethod=%s,%x", info->originalMethod, info->originalMethod);
	LOGD("info->paramTypes=%s,%x", info->paramTypes, info->paramTypes);
	LOGD("info->returnType=%s,%x", info->returnType, info->returnType);
	// save info to ApiHooker save结构体中
	switch(apiHookerFlag){
		case(START):
			temp->save.classDesc = info->classDesc;
			temp->save.isStaticMethod = info->isStaticMethod;
			temp->save.methodName = info->methodName;
			temp->save.methodSig = info->methodSig;
			temp->save.originalMethod = info->originalMethod;
			temp->save.paramTypes = info->paramTypes;
			temp->save.returnType = info->returnType;
			method->nativeFunc = startMethodHandler;
			LOGI("[+] %s->%s was hooked\n", classDesc, methodName);
			break;
		case(ONCREATE):
			temp->save.classDesc = info->classDesc;
			temp->save.isStaticMethod = info->isStaticMethod;
			temp->save.methodName = info->methodName;
			temp->save.methodSig = info->methodSig;
			temp->save.originalMethod = info->originalMethod;
			temp->save.paramTypes = info->paramTypes;
			temp->save.returnType = info->returnType;
			method->nativeFunc = onCreateMethodHandler;
			LOGI("[+] %s->%s was hooked\n", classDesc, methodName);
			break;
		case(GETMACADDRESS):
			temp->save.classDesc = info->classDesc;
			temp->save.isStaticMethod = info->isStaticMethod;
			temp->save.methodName = info->methodName;
			temp->save.methodSig = info->methodSig;
			temp->save.originalMethod = info->originalMethod;
			temp->save.paramTypes = info->paramTypes;
			temp->save.returnType = info->returnType;
			method->nativeFunc = getMacAddressMethodHandler;
			LOGI("[+] %s->%s was hooked\n", classDesc, methodName);
			break;
	}

	return 0;
}
