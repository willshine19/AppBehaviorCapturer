# dvmInvokeMethod函数说明

标签（空格分隔）： 实验室

---

2015-10-13
作者：桑耀辉

---
##函数原型：
```
Object* dvmInvokeMethod(Object* obj, const Method* method, ArrayObject* argList, ArrayObject* params, ClassObject* returnType, bool noAccessCheck)
```
##作用：
该函数是android源码的一部分，源码位置在dalvik/vm/interp/Stack.cpp。作用是调用指定java层的方法。

##参数说明：
该函数的参数的含义是难点。
参数1：obj表示方法调用的主体，实例或者null（如果是static方法）
参数2：method可以直接使用hook之前copy的对象，
参数3：argList，在Proxy.cpp中用现成的boxMethodArgs方法
参数4：params用自己写的代码获取，dvmGetMethodParamTypes函数
参数5：returnType通过Reflect.h中dvmGetBoxedReturnType的函数获取
参数6：true

##返回值
返回值的类型是Object*，代表java层方法的返回值。无论返回值是何种类型，都可以再调用其toString方法将信息打印出来。

##举例：
AllHookInOne-v11.0/jni/AppBehaviorCapturer/ApiHooker/AndroidSystem/OnCreateActivityApiHooker.cpp中的参数解析部分代码
```cpp
    LOGD("开始解析oncreate方法的调用实例");
    JNIEnv *env = AndroidRuntime::getJNIEnv();
	jclass activity = env->FindClass("android/app/Activity");
	if (activity == 0) {
		LOGE("Get Class failed");
		return false;
	}
	LOGD("Find class successfully");

	jmethodID methodID = env->GetMethodID(activity, "toString",
			"()Ljava/lang/String;");
	if (methodID == 0) {
		LOGE("get method failed");
		return false;
	}
	LOGD("get method successfully");

	// 参数1
	Object* activityObject = (Object*) args[0];
	// 参数2
	Method* activityToString = (Method*) methodID;
	// 参数3
	u4* uriArgs = (u4*) 1;
	ArrayObject* argList = dvmBoxMethodArgs(activityToString, uriArgs);
	// 参数4
	ArrayObject* params = (ArrayObject *) dvmGetMethodParamTypes(activityToString,"()Ljava/lang/String;");
	// 参数5
	ClassObject* returnType = (ClassObject *) dvmGetBoxedReturnType(activityToString);
	// 调用这个方法
	Object* toStringResult = dvmInvokeMethod(activityObject, activityToString, argList,params, returnType, true);
    // 解析返回值
	StringObject* sourceNameObj = (StringObject*) toStringResult;
	char* paramString = dvmCreateCstrFromString(sourceNameObj);
	LOGD("[+] 调用实例为 %s", paramString);
```

###PS
该调用是支持多态的。比如说，现在有两个类，Activity和MainActivity，他们之间是继承关系，MainActivity是子类。Object*实际上表示的是子类，但是我们可以把它当做父类Activity，调用它的toString方法，此时返回的是子类的信息。

