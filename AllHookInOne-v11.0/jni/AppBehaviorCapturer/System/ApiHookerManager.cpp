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
	LOGE("-------------ApiHookerManager infosender ");
	this->mInfoSender = InfoSender::getInstance();
	mInfoSender->init();
	return 0;
}

/**
 * 初始化哈希表
 */bool ApiHookerManager::initHashMap() {
	//系统api
	StartThreadApiHooker* start = new StartThreadApiHooker();
	RunThreadApiHooker* run = new RunThreadApiHooker();
	OnCreateServiceApiHooker* onCreateService = new OnCreateServiceApiHooker();
	OnCreateActivityApiHooker* onCreate = new OnCreateActivityApiHooker();
	OnCreateApplicationApiHooker* OnCreateApplication =
			new OnCreateApplicationApiHooker();
	OnDestroyActivityApiHooker* onDestroy = new OnDestroyActivityApiHooker();
	OnPauseActivityApiHooker* onPause = new OnPauseActivityApiHooker();
	OnRestartActivityApiHooker* onRestart = new OnRestartActivityApiHooker();
	OnResumeActivityApiHooker* onResume = new OnResumeActivityApiHooker();
	OnStartActivityApiHooker* onStart = new OnStartActivityApiHooker();
//	OnStartServiceApiHooker*  onStartService = new OnStartServiceApiHooker();
	onStartCommandServiceApiHooker* onStartCommandService =
			new onStartCommandServiceApiHooker();
	OnStopActivityApiHooker* onStop = new OnStopActivityApiHooker();

	mApiHookerHashMap.insert(make_pair("onCreate", onCreate));
	mApiHookerHashMap.insert(make_pair("onDestroy", onDestroy));
	mApiHookerHashMap.insert(make_pair("onPause", onPause));
	mApiHookerHashMap.insert(make_pair("onRestart", onRestart));
	mApiHookerHashMap.insert(make_pair("onStart", onStart));
	mApiHookerHashMap.insert(make_pair("onStop", onStop));
	mApiHookerHashMap.insert(make_pair("onResume", onResume));
//	mApiHookerHashMap.insert(make_pair("OnCreateApplicationLandroid/app/Application", OnCreateApplication));
//	mApiHookerHashMap.insert(make_pair("onCreateLandroid/app/Service;", onCreateService));//
//	mApiHookerHashMap.insert(make_pair("onStart", onStartService));
	mApiHookerHashMap.insert(
			make_pair("onStartCommandLandroid/app/Service;",
					onStartCommandService)); //Landroid/app/Service
	mApiHookerHashMap.insert(make_pair("startLjava/lang/Thread;", start));
	mApiHookerHashMap.insert(make_pair("run", run));
	LOGD("insert system api to hashmap successfully");

	//外设api
	OpenCamera* open = new OpenCamera();
	GetDefaultSensorSensorManager* getDefaultSensor =
			new GetDefaultSensorSensorManager();
	PrepareMediaRecorder* prepare = new PrepareMediaRecorder();
	ReadAudioRecord* readAudio = new ReadAudioRecord();
	ReleaseMediaRecorder* release = new ReleaseMediaRecorder();
	StartMediaRecorder* startMediaRecorder = new StartMediaRecorder();
	StartRecordingAudioRecord* startRecordingAudioRecord =
			new StartRecordingAudioRecord();
	mApiHookerHashMap.insert(make_pair("openLandroid/hardware/Camera;", open));
	mApiHookerHashMap.insert(make_pair("getDefaultSensor", getDefaultSensor));
	mApiHookerHashMap.insert(make_pair("prepare", prepare));
	mApiHookerHashMap.insert(
			make_pair("readLandroid/media/AudioRecord;", readAudio));
	mApiHookerHashMap.insert(make_pair("release", release));
	mApiHookerHashMap.insert(
			make_pair("startLandroid/media/MediaRecorder;",
					startMediaRecorder));
	mApiHookerHashMap.insert(
			make_pair("startRecording", startRecordingAudioRecord));
	LOGD("insert peripheral api to hashmap successfully");

	//数据api
	AddGpsStatusListenerLocationManager* addGpsStatusListener =
			new AddGpsStatusListenerLocationManager();
	CloseFileInputStream* closeFileInputStream = new CloseFileInputStream();
	CloseFileOutputStream* closeFileOutputStream = new CloseFileOutputStream();
	DeleteContentResolver* deleteContentResolver = new DeleteContentResolver();
	GetCallStateTelephonyManager* getCallState =
			new GetCallStateTelephonyManager();
	GetDeviceIdTelephonyApiHooker* getDeviceId =
			new GetDeviceIdTelephonyApiHooker();
	GetFDFileInputStream* getFD = new GetFDFileInputStream();
	GetLastKnownLocationApiHooker* getLastKnownLocation =
			new GetLastKnownLocationApiHooker();
	GetLine1NumberTelephonyManager* getLine1 =
			new GetLine1NumberTelephonyManager();
	GetMacAddressWifiInfoApiHooker* getMacAddress =
			new GetMacAddressWifiInfoApiHooker();
	GetMessageBodySmsMessage* getMessageBody = new GetMessageBodySmsMessage();
	GetSimSerialNumberTelephonyManager* getSimSerialNumber =
			new GetSimSerialNumberTelephonyManager();
	GetSubscriberIdTelephonyManager* getSubscriberId =
			new GetSubscriberIdTelephonyManager();
	InsertContentResolverApiHooker* insertContentResolver =
			new InsertContentResolverApiHooker();
	QueryContentResolverApiHooker* queryContentResolve =
			new QueryContentResolverApiHooker();
	RequestLocationUpdatesLocationManager* requestLocationUpdatas =
			new RequestLocationUpdatesLocationManager();
	UpdateContentResolver* updateContentResolver = new UpdateContentResolver();
	WriteFileOutputStreamApiHooker* writeFileOutputStream =
			new WriteFileOutputStreamApiHooker();
	ReadFileInputStream* readFileInputStream = new ReadFileInputStream();
//	 mApiHookerHashMap.insert(make_pair("insert", insertContentResolver));
//	 mApiHookerHashMap.insert(make_pair("query", queryContentResolve));
//	 mApiHookerHashMap.insert(make_pair("delete", deleteContentResolver));
	mApiHookerHashMap.insert(make_pair("update", updateContentResolver));
	mApiHookerHashMap.insert(make_pair("getMessageBody", getMessageBody));
	mApiHookerHashMap.insert(make_pair("getCallState", getCallState));
	mApiHookerHashMap.insert(make_pair("getDeviceId", getDeviceId));
	mApiHookerHashMap.insert(make_pair("getLine1Number", getLine1));
	mApiHookerHashMap.insert(
			make_pair("getSimSerialNumber", getSimSerialNumber));
	mApiHookerHashMap.insert(make_pair("getSubscriberId", getSubscriberId));
	mApiHookerHashMap.insert(
			make_pair("addGpsStatusListener", addGpsStatusListener));
	mApiHookerHashMap.insert(
			make_pair("getLastKnownLocation", getLastKnownLocation));
	mApiHookerHashMap.insert(
			make_pair("requestLocationUpdatas", requestLocationUpdatas));
	mApiHookerHashMap.insert(
			make_pair("readLjava/io/FileInputStream;", readFileInputStream));
	mApiHookerHashMap.insert(
			make_pair("closeLjava/io/FileInputStream;", closeFileInputStream));
	mApiHookerHashMap.insert(make_pair("getFD", getFD));
	mApiHookerHashMap.insert(
			make_pair("closeLjava/io/FileOutputStream;",
					closeFileOutputStream));
	mApiHookerHashMap.insert(make_pair("write", writeFileOutputStream));
	mApiHookerHashMap.insert(make_pair("getMacAddress", getMacAddress));
	LOGD("insert data api to hashmap successfully");

	// 通信 api
	CloseSocket* closeSocket = new CloseSocket();
	DisableBluetoothAdapter* disableBluetoothAdapter =
			new DisableBluetoothAdapter();
	DisconnectWifiManager* disconnect = new DisconnectWifiManager();
	EnableBluetoothAdapter* enableBluetoothAdapter =
			new EnableBluetoothAdapter();
	EnableNetworkWifiManager* enableNetwork = new EnableNetworkWifiManager();
	OpenConnectionURL* openConnection = new OpenConnectionURL();
	SendDataMessageSmsManager* sendDataMessage =
			new SendDataMessageSmsManager();
	SendMultipartTextMessageSmsManager* sendMultipartTextMessage =
			new SendMultipartTextMessageSmsManager();
	SendTextMessageSmsManager* sendTextMessage =
			new SendTextMessageSmsManager();
	CallTelephonnyApiHooker* call = new CallTelephonnyApiHooker();
	EndCallITelephonyApiHooker* endCall = new EndCallITelephonyApiHooker();
	SetWifiEnabledWifiManager* setWifiEnabled = new SetWifiEnabledWifiManager();
	mApiHookerHashMap.insert(make_pair("sendDataMessage", sendDataMessage));
	mApiHookerHashMap.insert(
			make_pair("sendMultipartTextMessage", sendMultipartTextMessage));
	mApiHookerHashMap.insert(make_pair("sendTextMessage", sendTextMessage));
	mApiHookerHashMap.insert(make_pair("disable", disableBluetoothAdapter));
	mApiHookerHashMap.insert(make_pair("enable", enableBluetoothAdapter));
	mApiHookerHashMap.insert(make_pair("closeLjava/net/Socket;", closeSocket));
	mApiHookerHashMap.insert(
			make_pair("openConnectionLjava/net/URL;", openConnection));
	mApiHookerHashMap.insert(make_pair("disconnect", disconnect));
	mApiHookerHashMap.insert(make_pair("enableNetwork", enableNetwork));
	mApiHookerHashMap.insert(make_pair("setWifiEnabled", setWifiEnabled));
	mApiHookerHashMap.insert(make_pair("call", call));
	mApiHookerHashMap.insert(make_pair("endCall", endCall));
	LOGD("insert communication api to hashmap successfully");

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

