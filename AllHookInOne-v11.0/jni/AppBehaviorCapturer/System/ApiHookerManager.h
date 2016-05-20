/*
 * ApiHookerManager.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */
#ifndef APIHOOKERMANAGER_H_
#define APIHOOKERMANAGER_H_
#include <string>
#include <jni.h>
#include <stdio.h>
#include "android_runtime/AndroidRuntime.h"
#include <unordered_map>

#include "../InfoSender/InfoSender.h"

#include "../ApiHooker/Androidapi/bindService0APIHOOKER.h"
#include "../ApiHooker/Androidapi/checkPermission0APIHOOKER.h"
#include "../ApiHooker/Androidapi/checkUriPermission0APIHOOKER.h"
#include "../ApiHooker/Androidapi/checkUriPermission1APIHOOKER.h"
#include "../ApiHooker/Androidapi/getAction0APIHOOKER.h"
#include "../ApiHooker/Androidapi/getData0APIHOOKER.h"
#include "../ApiHooker/Androidapi/getDataString0APIHOOKER.h"
#include "../ApiHooker/Androidapi/getExtras0APIHOOKER.h"
#include "../ApiHooker/Androidapi/getIntent0APIHOOKER.h"
#include "../ApiHooker/Androidapi/getPackageName0APIHOOKER.h"
#include "../ApiHooker/Androidapi/getResources0APIHOOKER.h"
#include "../ApiHooker/Androidapi/getSystemService0APIHOOKER.h"
#include "../ApiHooker/Androidapi/grantUriPermission0APIHOOKER.h"
#include "../ApiHooker/Androidapi/hasExtra0APIHOOKER.h"
#include "../ApiHooker/Androidapi/Intent0APIHOOKER.h"
#include "../ApiHooker/Androidapi/Intent1APIHOOKER.h"
#include "../ApiHooker/Androidapi/Intent2APIHOOKER.h"
#include "../ApiHooker/Androidapi/parseUri0APIHOOKER.h"
#include "../ApiHooker/Androidapi/putExtra0APIHOOKER.h"
#include "../ApiHooker/Androidapi/registerReceiver0APIHOOKER.h"
#include "../ApiHooker/Androidapi/registerReceiver1APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendBroadcast0APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendBroadcast1APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendBroadcast2APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendBroadcastAsUser0APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendBroadcastAsUser1APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendBroadcastAsUser2APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendBroadcastAsUser3APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendOrderedBroadcast0APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendOrderedBroadcast1APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendOrderedBroadcast2APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendOrderedBroadcast3APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendOrderedBroadcastAsUser0APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendOrderedBroadcastAsUser1APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendStickyBroadcast0APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendStickyBroadcast1APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendStickyBroadcastAsUser0APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendStickyBroadcastAsUser1APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendStickyOrderedBroadcast0APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendStickyOrderedBroadcast1APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendStickyOrderedBroadcastAsUser0APIHOOKER.h"
#include "../ApiHooker/Androidapi/sendStickyOrderedBroadcastAsUser1APIHOOKER.h"
#include "../ApiHooker/Androidapi/setAction0APIHOOKER.h"
#include "../ApiHooker/Androidapi/setData0APIHOOKER.h"
#include "../ApiHooker/Androidapi/startActivities0APIHOOKER.h"
#include "../ApiHooker/Androidapi/startActivity0APIHOOKER.h"
#include "../ApiHooker/Androidapi/startInstrumentation0APIHOOKER.h"
#include "../ApiHooker/Androidapi/startIntentSender0APIHOOKER.h"
#include "../ApiHooker/Androidapi/startService0APIHOOKER.h"
#include "../ApiHooker/Androidapi/stopService0APIHOOKER.h"
#include "../ApiHooker/Androidapi/unbindService0APIHOOKER.h"
#include "../ApiHooker/Androidapi/unregisterReceiver0APIHOOKER.h"

#include "../ApiInfo/CollectedApiInfo.h"
#include <typeinfo>
#include "../Utils/DalvikMethodHooker.h"
#include "../Utils/JavaMethodHooker.h"
#include "common.h"
#include <pthread.h>

using namespace __gnu_cxx;

class ApiHookerManager {
private:
	//使用单例模式，构造方法私有，声明一个private static变量，由getInstance方法访问
	static ApiHookerManager* apiHookerManagerInstance;
	ApiHookerManager();
	virtual ~ApiHookerManager();
	InfoSender* mInfoSender;bool initHashMap();bool hookJavaMethod();
	JNIEnv * getEnv();

public:
	//成员变量
	unordered_map<string, ApiHooker*> mApiHookerHashMap; //hashmap
	static pthread_mutex_t lock;
	JavaVM *mJavaVM;
	string mContextInfo; // 当前的上下文信息 全局变量

	//单例模式实例访问接口
	static ApiHookerManager* getInstance();
	//成员函数
	int main();
	InfoSender* getInfoSender();

};

#endif /* APIHOOKERMANAGER_H_ */
