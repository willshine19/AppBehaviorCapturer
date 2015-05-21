/*
 * ApiHookerManager.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */
#include <string>
#include <jni.h>
#include <stdio.h>
#include "android_runtime/AndroidRuntime.h"

//#include <ext/hash_map>
#include <unordered_map>
#include "../InfoSender/InfoSender.h"
#include "../ApiHooker/OnCreateActivityApiHooker.h"
#include "../ApiHooker/StartThreadApiHooker.h"
#include "../ApiHooker/GetMacAddressWifiInfoApiHooker.h"
#include "../ApiInfo/CollectedApiInfo.h"
#include <typeinfo>

#include "../Utils/JavaMethodHooker.h"
#include "common.h"
#ifndef APIHOOKERMANAGER_H_
#define APIHOOKERMANAGER_H_

using namespace __gnu_cxx;

class ApiHookerManager {
	private:
		//使用单例模式，构造方法私有，声明一个private static变量，由getInstance方法访问
		 static ApiHookerManager* apiHookerManagerInstance;
		 ApiHookerManager();
		 virtual ~ApiHookerManager();
		 InfoSender* mInfoSender;
		bool initHashMap();
		bool bindJavaMethodToNative();

	public:
		//成员变量
//		hash_map<string, ApiHooker> mApiHookerHashMap;
		 unordered_map<string, ApiHooker*> mApiHookerHashMap; //hashmap
		 JavaVM *mJavaVM;

		//单例模式实例访问接口
		static ApiHookerManager* getInstance();
		//成员函数
		JNIEnv * getEnv();
		bool init();
		InfoSender* getInfoSender();

};

#endif /* APIHOOKERMANAGER_H_ */
