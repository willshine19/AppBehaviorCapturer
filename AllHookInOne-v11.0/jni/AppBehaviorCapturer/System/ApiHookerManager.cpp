/*
 * ApiHookerManager.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#include "ApiHookerManager.h"

#include <iostream>
using namespace std;
using namespace __gnu_cxx;

/**
 * 构造函数
 */
ApiHookerManager::ApiHookerManager() {
	LOGD("construct ApiHookerManager successfully");
	// TODO Auto-generated constructor stub
	pthread_mutex_init(&ApiHookerManager::lock, NULL);
}

/**
 * 析构函数
 */
ApiHookerManager::~ApiHookerManager() {
	// TODO Auto-generated destructor stub
}

//静态成员变量初始化
ApiHookerManager* ApiHookerManager::apiHookerManagerInstance = NULL;
pthread_mutex_t ApiHookerManager::lock = PTHREAD_MUTEX_INITIALIZER;

/**
 * 单例模式
 * 返回ApiHookerManager类的唯一实例
 */
ApiHookerManager* ApiHookerManager::getInstance() {
	pthread_mutex_lock(&ApiHookerManager::lock);
	if (apiHookerManagerInstance == NULL) {
		apiHookerManagerInstance = new ApiHookerManager();
	}
	pthread_mutex_unlock(&ApiHookerManager::lock);
	return apiHookerManagerInstance;
}

/**
 * 返回JNIEnv的指针
 */
JNIEnv* ApiHookerManager::getEnv() {
	//获取JavaVM，由此可获取JNIEnv
	this->mJavaVM = android::AndroidRuntime::getJavaVM();
	LOGD("-------------Init successfully--------------\n");

	int status;
	JNIEnv *envnow = NULL;
	//使用指定的JNI版本，获取java环境
	status = mJavaVM->GetEnv((void **) &envnow, JNI_VERSION_1_4);
	if (status < 0) {
		//将当前C线程转为java线程
		status = mJavaVM->AttachCurrentThread(&envnow, NULL);
		if (status < 0) {
			return NULL;
		}
	}
	LOGD("-------------getEnv successfully--------------\n");
	return envnow;
}

/**
 * AppBehaviorCapturer系统 入口
 */
int ApiHookerManager::main() {
	LOGD("AppBehaviorCapturer system is running");
	//初始化系统中所有的ApiHooker，并将其装载至mApiHookerHashMap中
	initHashMap();
	hookJavaMethod();

	//获取系统发送模块的实例 初始化
	this->mInfoSender = InfoSender::getInstance();
	LOGE("-------------ApiHookerManager infosender ");
	mInfoSender->init();
	return 0;
}

/**
 * 初始化哈希表
 */bool ApiHookerManager::initHashMap() {
	 bindService0ApiHooker* bindService0 = new bindService0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("bindServiceLandroid/content/ContextWrapper;ZLLI",bindService0));
	 checkPermission0ApiHooker* checkPermission0 = new checkPermission0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("checkPermissionLandroid/content/ContextWrapper;ILII",checkPermission0));
	 checkUriPermission0ApiHooker* checkUriPermission0 = new checkUriPermission0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("checkUriPermissionLandroid/content/ContextWrapper;ILIII",checkUriPermission0));
	 checkUriPermission1ApiHooker* checkUriPermission1 = new checkUriPermission1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("checkUriPermissionLandroid/content/ContextWrapper;ILLLIII",checkUriPermission1));
	 getAction0ApiHooker* getAction0 = new getAction0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getActionLandroid/content/Intent;L",getAction0));
	 getData0ApiHooker* getData0 = new getData0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDataLandroid/content/Intent;L",getData0));
	 getDataString0ApiHooker* getDataString0 = new getDataString0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDataStringLandroid/content/Intent;L",getDataString0));
	 getExtras0ApiHooker* getExtras0 = new getExtras0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getExtrasLandroid/content/Intent;L",getExtras0));
	 getIntent0ApiHooker* getIntent0 = new getIntent0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getIntentLandroid/content/Intent;LL",getIntent0));
	 getPackageName0ApiHooker* getPackageName0 = new getPackageName0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getPackageNameLandroid/content/ContextWrapper;L",getPackageName0));
	 getResources0ApiHooker* getResources0 = new getResources0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getResourcesLandroid/content/ContextWrapper;L",getResources0));
	 getSystemService0ApiHooker* getSystemService0 = new getSystemService0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getSystemServiceLandroid/content/ContextWrapper;LL",getSystemService0));
	 grantUriPermission0ApiHooker* grantUriPermission0 = new grantUriPermission0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("grantUriPermissionLandroid/content/ContextWrapper;VLLI",grantUriPermission0));
	 hasExtra0ApiHooker* hasExtra0 = new hasExtra0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("hasExtraLandroid/content/Intent;ZL",hasExtra0));
	 Intent0ApiHooker* Intent0 = new Intent0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/content/Intent;V",Intent0));
	 Intent1ApiHooker* Intent1 = new Intent1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/content/Intent;VL",Intent1));
	 Intent2ApiHooker* Intent2 = new Intent2ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/content/Intent;VLL",Intent2));
	 parseUri0ApiHooker* parseUri0 = new parseUri0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("parseUriLandroid/content/Intent;LLI",parseUri0));
	 putExtra0ApiHooker* putExtra0 = new putExtra0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("putExtraLandroid/content/Intent;LLL",putExtra0));
	 registerReceiver0ApiHooker* registerReceiver0 = new registerReceiver0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("registerReceiverLandroid/content/ContextWrapper;LLLLL",registerReceiver0));
	 registerReceiver1ApiHooker* registerReceiver1 = new registerReceiver1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("registerReceiverLandroid/content/ContextWrapper;LLLLL",registerReceiver1));
	 sendBroadcast0ApiHooker* sendBroadcast0 = new sendBroadcast0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendBroadcastLandroid/content/ContextWrapper;VLL",sendBroadcast0));
	 sendBroadcast1ApiHooker* sendBroadcast1 = new sendBroadcast1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendBroadcastLandroid/content/ContextWrapper;VLL",sendBroadcast1));
	 sendBroadcast2ApiHooker* sendBroadcast2 = new sendBroadcast2ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendBroadcastLandroid/content/ContextWrapper;VLL",sendBroadcast2));
	 sendBroadcastAsUser0ApiHooker* sendBroadcastAsUser0 = new sendBroadcastAsUser0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendBroadcastAsUserLandroid/content/ContextWrapper;VLLL",sendBroadcastAsUser0));
	 sendBroadcastAsUser1ApiHooker* sendBroadcastAsUser1 = new sendBroadcastAsUser1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendBroadcastAsUserLandroid/content/ContextWrapper;VLLL",sendBroadcastAsUser1));
	 sendBroadcastAsUser2ApiHooker* sendBroadcastAsUser2 = new sendBroadcastAsUser2ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendBroadcastAsUserLandroid/content/ContextWrapper;VLL",sendBroadcastAsUser2));
	 sendBroadcastAsUser3ApiHooker* sendBroadcastAsUser3 = new sendBroadcastAsUser3ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendBroadcastAsUserLandroid/content/ContextWrapper;VLLL",sendBroadcastAsUser3));
	 sendOrderedBroadcast0ApiHooker* sendOrderedBroadcast0 = new sendOrderedBroadcast0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendOrderedBroadcastLandroid/content/ContextWrapper;VLLLLILL",sendOrderedBroadcast0));
	 sendOrderedBroadcast1ApiHooker* sendOrderedBroadcast1 = new sendOrderedBroadcast1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendOrderedBroadcastLandroid/content/ContextWrapper;VLL",sendOrderedBroadcast1));
	 sendOrderedBroadcast2ApiHooker* sendOrderedBroadcast2 = new sendOrderedBroadcast2ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendOrderedBroadcastLandroid/content/ContextWrapper;VLLLLILL",sendOrderedBroadcast2));
	 sendOrderedBroadcast3ApiHooker* sendOrderedBroadcast3 = new sendOrderedBroadcast3ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendOrderedBroadcastLandroid/content/ContextWrapper;VLL",sendOrderedBroadcast3));
	 sendOrderedBroadcastAsUser0ApiHooker* sendOrderedBroadcastAsUser0 = new sendOrderedBroadcastAsUser0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendOrderedBroadcastAsUserLandroid/content/ContextWrapper;VLLLLLILL",sendOrderedBroadcastAsUser0));
	 sendOrderedBroadcastAsUser1ApiHooker* sendOrderedBroadcastAsUser1 = new sendOrderedBroadcastAsUser1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendOrderedBroadcastAsUserLandroid/content/ContextWrapper;VLLLLLILL",sendOrderedBroadcastAsUser1));
	 sendStickyBroadcast0ApiHooker* sendStickyBroadcast0 = new sendStickyBroadcast0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendStickyBroadcastLandroid/content/ContextWrapper;VL",sendStickyBroadcast0));
	 sendStickyBroadcast1ApiHooker* sendStickyBroadcast1 = new sendStickyBroadcast1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendStickyBroadcastLandroid/content/ContextWrapper;VL",sendStickyBroadcast1));
	 sendStickyBroadcastAsUser0ApiHooker* sendStickyBroadcastAsUser0 = new sendStickyBroadcastAsUser0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendStickyBroadcastAsUserLandroid/content/ContextWrapper;VLL",sendStickyBroadcastAsUser0));
	 sendStickyBroadcastAsUser1ApiHooker* sendStickyBroadcastAsUser1 = new sendStickyBroadcastAsUser1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendStickyBroadcastAsUserLandroid/content/ContextWrapper;VLL",sendStickyBroadcastAsUser1));
	 sendStickyOrderedBroadcast0ApiHooker* sendStickyOrderedBroadcast0 = new sendStickyOrderedBroadcast0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendStickyOrderedBroadcastLandroid/content/ContextWrapper;VLLLILL",sendStickyOrderedBroadcast0));
	 sendStickyOrderedBroadcast1ApiHooker* sendStickyOrderedBroadcast1 = new sendStickyOrderedBroadcast1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendStickyOrderedBroadcastLandroid/content/ContextWrapper;VLLLILL",sendStickyOrderedBroadcast1));
	 sendStickyOrderedBroadcastAsUser0ApiHooker* sendStickyOrderedBroadcastAsUser0 = new sendStickyOrderedBroadcastAsUser0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendStickyOrderedBroadcastAsUserLandroid/content/ContextWrapper;VLLLLILL",sendStickyOrderedBroadcastAsUser0));
	 sendStickyOrderedBroadcastAsUser1ApiHooker* sendStickyOrderedBroadcastAsUser1 = new sendStickyOrderedBroadcastAsUser1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendStickyOrderedBroadcastAsUserLandroid/content/ContextWrapper;VLLLLILL",sendStickyOrderedBroadcastAsUser1));
	 setAction0ApiHooker* setAction0 = new setAction0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setActionLandroid/content/Intent;LL",setAction0));
	 setData0ApiHooker* setData0 = new setData0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setDataLandroid/content/Intent;LL",setData0));
	 startActivities0ApiHooker* startActivities0 = new startActivities0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("startActivitiesLandroid/content/ContextWrapper;VLL",startActivities0));
	 startActivity0ApiHooker* startActivity0 = new startActivity0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("startActivityLandroid/content/ContextWrapper;VLL",startActivity0));
	 startInstrumentation0ApiHooker* startInstrumentation0 = new startInstrumentation0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("startInstrumentationLandroid/content/ContextWrapper;ZLLL",startInstrumentation0));
	 startIntentSender0ApiHooker* startIntentSender0 = new startIntentSender0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("startIntentSenderLandroid/content/ContextWrapper;VLLIIIL",startIntentSender0));
	 startService0ApiHooker* startService0 = new startService0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("startServiceLandroid/content/ContextWrapper;LL",startService0));
	 stopService0ApiHooker* stopService0 = new stopService0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("stopServiceLandroid/content/ContextWrapper;ZL",stopService0));
	 unbindService0ApiHooker* unbindService0 = new unbindService0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("unbindServiceLandroid/content/ContextWrapper;VL",unbindService0));
	 unregisterReceiver0ApiHooker* unregisterReceiver0 = new unregisterReceiver0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("unregisterReceiverLandroid/content/ContextWrapper;VL",unregisterReceiver0));
	LOGD("insert system api to hashmap successfully");
	return true;
}

/**
 * 遍历哈希表，hook哈希表中记录的所有目标java层api
 * 封装了dalvikJavaMethodHook函数
 */bool ApiHookerManager::hookJavaMethod() {
	JNIEnv *env = getEnv();
	HookInfo info;
	JavaMethodHooker* javaMethodHooker = new JavaMethodHooker();
	ApiHooker* tempApiHooker;
	ApiDeclaration tempApiDeclaration;

	// 遍历 哈希表
	unordered_map<string, ApiHooker*>::iterator map_it =
			mApiHookerHashMap.begin();
	//哈西表每个ApiHooker的绑定过程
	while (map_it != mApiHookerHashMap.end()) {
		// step 1;
		//获取哈西表中的键值
		tempApiHooker = map_it->second;

		// step 2;
		if (&tempApiHooker == NULL) {
			LOGE(
					"[-] bindJavaMethodToNative: getting ApiHooker from mApiHookerHashMap failed");
			break;
		}
		tempApiDeclaration = tempApiHooker->getApiDeclaration();
		info.classDesc = tempApiDeclaration.getClassName().c_str();
		info.methodName = tempApiDeclaration.getApiName().c_str();
		info.methodSig = tempApiDeclaration.getApiSignature().c_str();
		info.isStaticMethod = tempApiDeclaration.isStaticMethod();
		info.originalMethod = tempApiDeclaration.getOriginalMethod();
		info.paramTypes = tempApiDeclaration.getParamTapes();
		info.returnType = tempApiDeclaration.getReturnType();

		// step 3 关键 hook的核心逻辑
//		javaMethodHooker->hookJavaMethod(env, tempApiHooker, &info);
		dalvikJavaMethodHook(env, tempApiHooker, &info);

		// step 4
		map_it++;
	}
	return true;
}

/**
 * 返回 InfoSender的实例
 */
InfoSender* ApiHookerManager::getInfoSender() {
	if (mInfoSender != NULL) {
		return this->mInfoSender;
	}
	return NULL;
}

