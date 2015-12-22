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
#include "../ApiHooker/AndroidSystem/OnCreateActivityApiHooker.h"
#include "../ApiHooker/AndroidSystem/OnCreateServiceApiHooker.h"
#include "../ApiHooker/AndroidSystem/OnCreateApplicationApiHooker.h"
#include "../ApiHooker/AndroidSystem/OnDestroyActivityApiHooker.h"
#include "../ApiHooker/AndroidSystem/OnPauseActivityApiHooker.h"
#include "../ApiHooker/AndroidSystem/OnRestartActivityApiHooker.h"
#include "../ApiHooker/AndroidSystem/OnResumeActivityApiHooker.h"
#include "../ApiHooker/AndroidSystem/OnStartActivityApiHooker.h"
//#include "../ApiHooker/AndroidSystem/OnStartServiceApiHooker.h"
#include "../ApiHooker/AndroidSystem/onStartCommandServiceApiHooker.h"
#include "../ApiHooker/AndroidSystem/OnStopActivityApiHooker.h"
#include "../ApiHooker/AndroidSystem/OnRestartActivityApiHooker.h"
#include "../ApiHooker/AndroidSystem/StartThreadApiHooker.h"
#include "../ApiHooker/AndroidSystem/RunThreadApiHooker.h"
#include "../ApiHooker/AndroidPeripheral/OpenCamera.h"
#include "../ApiHooker/AndroidPeripheral/GetDefaultSensorSensorManager.h"
#include "../ApiHooker/AndroidPeripheral/PrepareMediaRecorder.h"
#include "../ApiHooker/AndroidPeripheral/ReadAudioRecord.h"
#include "../ApiHooker/AndroidPeripheral/ReleaseMediaRecorder.h"
#include "../ApiHooker/AndroidPeripheral/StartMediaRecorder.h"
#include "../ApiHooker/AndroidPeripheral/StartRecordingAudioRecord.h"
#include "../ApiHooker/AndroidData/AddGpsStatusListenerLocationManager.h"
#include "../ApiHooker/AndroidData/ReadFileInputStream.h"
#include "../ApiHooker/AndroidData/CloseFileInputStream.h"
#include "../ApiHooker/AndroidData/CloseFileOutputStream.h"
#include "../ApiHooker/AndroidData/DeleteContentResolver.h"
#include "../ApiHooker/AndroidData/GetCallStateTelephonyManager.h"
#include "../ApiHooker/AndroidData/GetDeviceIdTelephonyApiHooker.h"
#include "../ApiHooker/AndroidData/GetFDFileInputStream.h"
#include "../ApiHooker/AndroidData/GetLastKnownLocationApiHooker.h"
#include "../ApiHooker/AndroidData/GetLine1NumberTelephonyManager.h"
#include "../ApiHooker/AndroidData/GetMacAddressWifiInfoApiHooker.h"
#include "../ApiHooker/AndroidData/GetMessageBodySmsMessage.h"
#include "../ApiHooker/AndroidData/GetSimSerialNumberTelephonyManager.h"
#include "../ApiHooker/AndroidData/GetSubscriberIdTelephonyManager.h"
#include "../ApiHooker/AndroidData/InsertContentResolverApiHooker.h"
#include "../ApiHooker/AndroidData/QueryContentResolverApiHooker.h"
#include "../ApiHooker/AndroidData/RequestLocationUpdatesLocationManager.h"
#include "../ApiHooker/AndroidData/UpdateContentResolver.h"
#include "../ApiHooker/AndroidData/WriteFileOutputStreamApiHooker.h"
#include "../ApiHooker/AndroidCommunication/CloseSocket.h"
#include "../ApiHooker/AndroidCommunication/DisableBluetoothAdapter.h"
#include "../ApiHooker/AndroidCommunication/DisconnectWifiManager.h"
#include "../ApiHooker/AndroidCommunication/EnableBluetoothAdapter.h"
#include "../ApiHooker/AndroidCommunication/EnableNetworkWifiManager.h"
#include "../ApiHooker/AndroidCommunication/OpenConnectionURL.h"
#include "../ApiHooker/AndroidCommunication/SendDataMessageSmsManager.h"
#include "../ApiHooker/AndroidCommunication/SendMultipartTextMessageSmsManager.h"
#include "../ApiHooker/AndroidCommunication/SendTextMessageSmsManager.h"
#include "../ApiHooker/AndroidCommunication/SetWifiEnabledWifiManager.h"
#include "../ApiHooker/AndroidCommunication/CallTelephonnyApiHooker.h"
#include "../ApiHooker/AndroidCommunication/EndCallITelephonyApiHooker.h"
#include "../ApiInfo/CollectedApiInfo.h"
#include <typeinfo>
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
		 InfoSender* mInfoSender;
		bool initHashMap();
		bool bindJavaMethodToNative();

	public:
		//成员变量
//		hash_map<string, ApiHooker> mApiHookerHashMap;
		 unordered_map<string, ApiHooker*> mApiHookerHashMap; //hashmap
		 static pthread_mutex_t lock;
		 JavaVM *mJavaVM;
		 string mcontextinfo;

		//单例模式实例访问接口
		static ApiHookerManager* getInstance();
		//成员函数
		JNIEnv * getEnv();
		bool init();
		InfoSender* getInfoSender();

};

#endif /* APIHOOKERMANAGER_H_ */
