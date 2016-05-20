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
/*
	 addListenerApiHooker* addListener = new addListenerApiHooker();
	 mApiHookerHashMap.insert(make_pair("addUpdateListenerLandroid/animation/ValueAnimator;VL",addListener));
//	 AnimationApiHooker* Animation = new AnimationApiHooker();
//	 mApiHookerHashMap.insert(make_pair("<init>Landroid/view/animation/Animation;V",Animation));
	 appendRecordApiHooker* appendRecord = new appendRecordApiHooker();
	 mApiHookerHashMap.insert(make_pair("appendRecordLandroid/view/accessibility/AccessibilityEvent;VL",appendRecord));
//	 BigDecimalApiHooker* BigDecimal = new BigDecimalApiHooker();
//	 mApiHookerHashMap.insert(make_pair("<init>Ljava/math/BigDecimal;VI",BigDecimal));
//	 ButtonApiHooker* Button = new ButtonApiHooker();
//	 mApiHookerHashMap.insert(make_pair("<init>Landroid/widget/Button;VL",Button));
//	 ClickableSpanApiHooker* ClickableSpan = new ClickableSpanApiHooker();
//	 mApiHookerHashMap.insert(make_pair("<init>Landroid/text/style/ClickableSpan;V",ClickableSpan));
	 decodeApiHooker* decode = new decodeApiHooker();
	 mApiHookerHashMap.insert(make_pair("decodeLjava/net/URLDecoder;LL",decode));
	 drawApiHooker* draw = new drawApiHooker();
	 mApiHookerHashMap.insert(make_pair("drawLandroid/graphics/drawable/DrawableContainer;VL",draw));
	 enableApiHooker* enable = new enableApiHooker();
	 mApiHookerHashMap.insert(make_pair("enableLandroid/bluetooth/BluetoothAdapter;Z",enable));
	 encodeApiHooker* encode = new encodeApiHooker();
	 mApiHookerHashMap.insert(make_pair("encodeLjava/net/URLEncoder;LL",encode));
	 execApiHooker* exec = new execApiHooker();
	 mApiHookerHashMap.insert(make_pair("execLjava/lang/Runtime;LLLL",exec));
	 FileApiHooker* File = new FileApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Ljava/io/File;VL",File));
	 FileInputStreamApiHooker* FileInputStream = new FileInputStreamApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Ljava/io/FileInputStream;VL",FileInputStream));
	 FileOutputStreamApiHooker* FileOutputStream = new FileOutputStreamApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Ljava/io/FileOutputStream;VL",FileOutputStream));
	 GestureDetectorApiHooker* GestureDetector = new GestureDetectorApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/view/GestureDetector;VLL",GestureDetector));
//	 getAction2ApiHooker* getAction2 = new getAction2ApiHooker();
//	 mApiHookerHashMap.insert(make_pair("getActionLandroid/view/MotionEvent;I",getAction2));
//	 getActionApiHooker* getAction = new getActionApiHooker();
//	 mApiHookerHashMap.insert(make_pair("getActionLandroid/KeyEvent;I",getAction));
	 getBaseStationIdApiHooker* getBaseStationId = new getBaseStationIdApiHooker();
	 mApiHookerHashMap.insert(make_pair("getBaseStationIdLandroid/telephony/cdma/CdmaCellLocation;I",getBaseStationId));
	 getConnectionInfoApiHooker* getConnectionInfo = new getConnectionInfoApiHooker();
	 mApiHookerHashMap.insert(make_pair("getConnectionInfoLandroid/net/wifi/WifiManager;L",getConnectionInfo));
	 getDeviceIdApiHooker* getDeviceId = new getDeviceIdApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDeviceIdLandroid/telephony/TelephonyManager;L",getDeviceId));
	 getExternalStorageDirectoryApiHooker* getExternalStorageDirectory = new getExternalStorageDirectoryApiHooker();
	 mApiHookerHashMap.insert(make_pair("getExternalStorageDirectoryLandroid/os/Environment;L",getExternalStorageDirectory));
	 getInstanceApiHooker* getInstance = new getInstanceApiHooker();
	 mApiHookerHashMap.insert(make_pair("getInstanceLandroid/webkit/CookieManager;L",getInstance));
	 getIntApiHooker* getInt = new getIntApiHooker();
	 mApiHookerHashMap.insert(make_pair("getIntLandroid/database/CursorWindow;III",getInt));
	 getLacApiHooker* getLac = new getLacApiHooker();
	 mApiHookerHashMap.insert(make_pair("getLacLandroid/telephony/gsm/GsmCellLocation;I",getLac));
	 getLine1NumberApiHooker* getLine1Number = new getLine1NumberApiHooker();
	 mApiHookerHashMap.insert(make_pair("getLine1NumberLandroid/telephony/TelephonyManager;L",getLine1Number));
	 getLongitudeApiHooker* getLongitude = new getLongitudeApiHooker();
	 mApiHookerHashMap.insert(make_pair("getLongitudeLandroid/location/Location;D",getLongitude));
	 GetMessageBodySmsMessage* GetMessageBody = new GetMessageBodySmsMessage();
	 mApiHookerHashMap.insert(make_pair("getMessageBodyLandroid/telephony/gsm/SmsMessage;L",GetMessageBody));
	 getPackageInfoApiHooker* getPackageInfo = new getPackageInfoApiHooker();
	 mApiHookerHashMap.insert(make_pair("getPackageInfoLandroid/content/pm/PackageManager;LLI",getPackageInfo));
	 GetSimSerialNumberTelephonyManager* GetSimSerialNumber = new GetSimSerialNumberTelephonyManager();
	 mApiHookerHashMap.insert(make_pair("getSimSerialNumberLandroid/telephony/TelephonyManager;L",GetSimSerialNumber));
	 getStringApiHooker* getString = new getStringApiHooker();
	 mApiHookerHashMap.insert(make_pair("getStringLandroid/database/CursorWindow;LII",getString));
	 getSystemServiceApiHooker* getSystemService = new getSystemServiceApiHooker();
	 mApiHookerHashMap.insert(make_pair("getSystemServiceLandroid/view/ContextThemeWrapper;LL",getSystemService));
	 getWidthApiHooker* getWidth = new getWidthApiHooker();
	 mApiHookerHashMap.insert(make_pair("getWidthLandroid/view/Display;I",getWidth));
	 GLSurfaceViewApiHooker* GLSurfaceView = new GLSurfaceViewApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/opengl/GLSurfaceView;VL",GLSurfaceView));
	 HttpURLConnectionApiHooker* HttpURLConnection = new HttpURLConnectionApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Ljava/net/HttpURLConnection;VL",HttpURLConnection));
	 insertApiHooker* insert = new insertApiHooker();
	 mApiHookerHashMap.insert(make_pair("insertLandroid/database/sqlite/SQLiteDatabase;JLLL",insert));
	 isTouchExplorationEnabledApiHooker* isTouchExplorationEnabled = new isTouchExplorationEnabledApiHooker();
	 mApiHookerHashMap.insert(make_pair("isTouchExplorationEnabledLandroid/view/accessibility/AccessibilityManager;Z",isTouchExplorationEnabled));
	 KillBackgroundProcessesApiHooker* KillBackgroundProcesses = new KillBackgroundProcessesApiHooker();
	 mApiHookerHashMap.insert(make_pair("killBackgroundProcessesLandroid/app/ActivityManager;VL",KillBackgroundProcesses));
	 LinkMovementMethodApiHooker* LinkMovementMethod = new LinkMovementMethodApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/text/method/LinkMovementMethod;V",LinkMovementMethod));
	 loadUrlApiHooker* loadUrl = new loadUrlApiHooker();
	 mApiHookerHashMap.insert(make_pair("loadUrlLandroid/webkit/WebView;VL",loadUrl));
	 MediaPlayerApiHooker* MediaPlayer = new MediaPlayerApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/media/MediaPlayer;V",MediaPlayer));
	 mkdirApiHooker* mkdir = new mkdirApiHooker();
	 mApiHookerHashMap.insert(make_pair("mkdirLjava/io/File;Z",mkdir));
	 obtainApiHooker* obtain = new obtainApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/os/Message;V",obtain));
	 onAccuracyChangedApiHooker* onAccuracyChanged = new onAccuracyChangedApiHooker();
	 mApiHookerHashMap.insert(make_pair("onAccuracyChangedLandroid/view/OrientationListener;VII",onAccuracyChanged));
	 OnClick1ApiHooker* OnClick1 = new OnClick1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("onClickLandroid/preference/PreferenceScreen;V",OnClick1));
	 OnClick2ApiHooker* OnClick2 = new OnClick2ApiHooker();
	 mApiHookerHashMap.insert(make_pair("onClickLandroid/preference/Preference;V",OnClick2));
	 OnClick3ApiHooker* OnClick3 = new OnClick3ApiHooker();
	 mApiHookerHashMap.insert(make_pair("onClickLandroid/widget/Spinner;VLI",OnClick3));
	 OnClick4ApiHooker* OnClick4 = new OnClick4ApiHooker();
	 mApiHookerHashMap.insert(make_pair("onClickLandroid/app/DatePickerDialog;VLI",OnClick4));
	 OnClick5ApiHooker* OnClick5 = new OnClick5ApiHooker();
	 mApiHookerHashMap.insert(make_pair("onClickLandroid/text/method/CharacterPickerDialog;VL",OnClick5));
	 OnClickApiHooker* OnClick = new OnClickApiHooker();
	 mApiHookerHashMap.insert(make_pair("onClickLandroid/widget/QuickContactBadge;VL",OnClick));
	 onCreateApiHooker* onCreate = new onCreateApiHooker();
	 mApiHookerHashMap.insert(make_pair("onCreateLandroid/app/Activity;VL",onCreate));
	 onDoubleTapEventApiHooker* onDoubleTapEvent = new onDoubleTapEventApiHooker();
	 mApiHookerHashMap.insert(make_pair("onDoubleTapEventLandroid/view/GestureDetector$SimpleOnGestureListener;ZL",onDoubleTapEvent));
	 onDownApiHooker* onDown = new onDownApiHooker();
	 mApiHookerHashMap.insert(make_pair("onDownLandroid/view/GestureDetector$SimpleOnGestureListener;ZL",onDown));
	 onDownApiHooker1* onDown1 = new onDownApiHooker1();
	 mApiHookerHashMap.insert(make_pair("onDownLandroid/widget/Gallery;ZL",onDown1));
	 onFlingApiHooker* onFling = new onFlingApiHooker();
	 mApiHookerHashMap.insert(make_pair("onFlingLandroid/view/GestureDetector$SimpleOnGestureListener;ZLLFF",onFling));
	 onFlingApiHooker1* onFling1 = new onFlingApiHooker1();
	 mApiHookerHashMap.insert(make_pair("onFlingLandroid/widget/Gallery;ZLLFF",onFling1));
	 onKeyDown1ApiHooker* onKeyDown1 = new onKeyDown1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("onKeyDownLandroid/app/Activity;ZIL",onKeyDown1));
	 onKeyDownApiHooker* onKeyDown = new onKeyDownApiHooker();
	 mApiHookerHashMap.insert(make_pair("onKeyDownLandroid/view/View;ZIL",onKeyDown));
//	 onKeyDownApiHooker10* onKeyDown10 = new onKeyDownApiHooker10();
//	 mApiHookerHashMap.insert(make_pair("onKeyDownLandroid/support/v7/widget/SearchView;ZIL",onKeyDown10));
	 onKeyDownApiHooker2* onKeyDown2 = new onKeyDownApiHooker2();
	 mApiHookerHashMap.insert(make_pair("onKeyDownLandroid/widget/TextView;ZIL",onKeyDown2));
	 onKeyDownApiHooker3* onKeyDown3 = new onKeyDownApiHooker3();
	 mApiHookerHashMap.insert(make_pair("onKeyDownLandroid/widget/VideoView;ZIL",onKeyDown3));
	 onKeyDownApiHooker4* onKeyDown4 = new onKeyDownApiHooker4();
	 mApiHookerHashMap.insert(make_pair("onKeyDownLandroid/webkit/WebView;ZIL",onKeyDown4));
	 onKeyDownApiHooker5* onKeyDown5 = new onKeyDownApiHooker5();
	 mApiHookerHashMap.insert(make_pair("onKeyDownLandroid/widget/ListPopupWindow;ZIL",onKeyDown5));
	 onKeyDownApiHooker6* onKeyDown6 = new onKeyDownApiHooker6();
	 mApiHookerHashMap.insert(make_pair("onKeyDownLandroid/widget/ListView;ZIL",onKeyDown6));
	 onKeyDownApiHooker7* onKeyDown7 = new onKeyDownApiHooker7();
	 mApiHookerHashMap.insert(make_pair("onKeyDownLandroid/widget/AbsListView;ZIL",onKeyDown7));
	 onKeyDownApiHooker8* onKeyDown8 = new onKeyDownApiHooker8();
	 mApiHookerHashMap.insert(make_pair("onKeyDownLandroid/widget/SearchView;ZIL",onKeyDown8));
	 onKeyDownApiHooker9* onKeyDown9 = new onKeyDownApiHooker9();
	 mApiHookerHashMap.insert(make_pair("onKeyDownLandroid/app/Dialog;ZIL",onKeyDown9));
	 onKeyMultipleApiHooker* onKeyMultiple = new onKeyMultipleApiHooker();
	 mApiHookerHashMap.insert(make_pair("onKeyMultipleLandroid/view/View;ZIIL",onKeyMultiple));
	 onKeyMultipleApiHooker1* onKeyMultiple1 = new onKeyMultipleApiHooker1();
	 mApiHookerHashMap.insert(make_pair("onKeyMultipleLandroid/app/Dialog;ZIIL",onKeyMultiple1));
	 onKeyMultipleApiHooker2* onKeyMultiple2 = new onKeyMultipleApiHooker2();
	 mApiHookerHashMap.insert(make_pair("onKeyMultipleLandroid/widget/GridView;ZIIL",onKeyMultiple2));
	 onKeyMultipleApiHooker3* onKeyMultiple3 = new onKeyMultipleApiHooker3();
	 mApiHookerHashMap.insert(make_pair("onKeyMultipleLandroid/widget/ListView;ZIIL",onKeyMultiple3));
	 onKeyMultipleApiHooker4* onKeyMultiple4 = new onKeyMultipleApiHooker4();
	 mApiHookerHashMap.insert(make_pair("onKeyMultipleLandroid/widget/TextView;ZIIL",onKeyMultiple4));
	 onKeyMultipleApiHooker5* onKeyMultiple5 = new onKeyMultipleApiHooker5();
	 mApiHookerHashMap.insert(make_pair("onKeyMultipleLandroid/app/Activity;ZIIL",onKeyMultiple5));
	 onKeyUpApiHooker* onKeyUp = new onKeyUpApiHooker();
	 mApiHookerHashMap.insert(make_pair("onKeyUpLandroid/view/View;ZIL",onKeyUp));
	 onKeyUpApiHooker1* onKeyUp1 = new onKeyUpApiHooker1();
	 mApiHookerHashMap.insert(make_pair("onKeyUpLandroid/app/Activity;ZIL",onKeyUp1));
	 onKeyUpApiHooker2* onKeyUp2 = new onKeyUpApiHooker2();
	 mApiHookerHashMap.insert(make_pair("onKeyUpLandroid/widget/TextView;ZIL",onKeyUp2));
	 onKeyUpApiHooker3* onKeyUp3 = new onKeyUpApiHooker3();
	 mApiHookerHashMap.insert(make_pair("onKeyUpLandroid/widget/AbsListView;ZIL",onKeyUp3));
	 onKeyUpApiHooker4* onKeyUp4 = new onKeyUpApiHooker4();
	 mApiHookerHashMap.insert(make_pair("onKeyUpLandroid/webkit/WebView;ZIL",onKeyUp4));
	 onKeyUpApiHooker5* onKeyUp5 = new onKeyUpApiHooker5();
	 mApiHookerHashMap.insert(make_pair("onKeyUpLandroid/widget/ListPopupWindow;ZIL",onKeyUp5));
	 onKeyUpApiHooker6* onKeyUp6 = new onKeyUpApiHooker6();
	 mApiHookerHashMap.insert(make_pair("onKeyUpLandroid/widget/ListView;ZIL",onKeyUp6));
	 onKeyUpApiHooker7* onKeyUp7 = new onKeyUpApiHooker7();
	 mApiHookerHashMap.insert(make_pair("onKeyUpLandroid/app/Dialog;ZIL",onKeyUp7));
	 OnLongClickApiHooker* OnLongClick = new OnLongClickApiHooker();
	 mApiHookerHashMap.insert(make_pair("onLongClickLandroid/widget/ZoomButton;ZL",OnLongClick));
	 onLongPressApiHooker* onLongPress = new onLongPressApiHooker();
	 mApiHookerHashMap.insert(make_pair("onLongPressLandroid/view/GestureDetector$SimpleOnGestureListener;VL",onLongPress));
	 onLongPressApiHooker1* onLongPress1 = new onLongPressApiHooker1();
	 mApiHookerHashMap.insert(make_pair("onLongPressLandroid/widget/Gallery;VL",onLongPress1));
	 onLongPressApiHooker2* onLongPress2 = new onLongPressApiHooker2();
	 mApiHookerHashMap.insert(make_pair("onLongPressLandroid/inputmethodservice/KeyboardView;ZL",onLongPress2));
	 onScrollApiHooker* onScroll = new onScrollApiHooker();
	 mApiHookerHashMap.insert(make_pair("onScrollLandroid/view/GestureDetector$SimpleOnGestureListener;ZLLFF",onScroll));
	 onScrollApiHooker1* onScroll1 = new onScrollApiHooker1();
	 mApiHookerHashMap.insert(make_pair("onScrollLandroid/widget/Gallery;ZLLFF",onScroll1));
	 onSensorChangedApiHooker* onSensorChanged = new onSensorChangedApiHooker();
	 mApiHookerHashMap.insert(make_pair("onSensorChangedLandroid/view/OrientationListener;VIF",onSensorChanged));
	 onShowPressApiHooker* onShowPress = new onShowPressApiHooker();
	 mApiHookerHashMap.insert(make_pair("onShowPressLandroid/widget/Gallery;VL",onShowPress));
	 onShowPressApiHooker1* onShowPress1 = new onShowPressApiHooker1();
	 mApiHookerHashMap.insert(make_pair("onShowPressLandroid/view/GestureDetector$SimpleOnGestureListener;VL",onShowPress1));
	 onSingleTapConfirmedApiHooker* onSingleTapConfirmed = new onSingleTapConfirmedApiHooker();
	 mApiHookerHashMap.insert(make_pair("onSingleTapConfirmedLandroid/view/GestureDetector$SimpleOnGestureListener;ZL",onSingleTapConfirmed));
	 onSingleTapUPApiHooker* onSingleTapUP = new onSingleTapUPApiHooker();
	 mApiHookerHashMap.insert(make_pair("onSingleTapUpLandroid/view/GestureDetector$SimpleOnGestureListener;ZL",onSingleTapUP));
	 onSingleTapUPApiHooker1* onSingleTapUP1 = new onSingleTapUPApiHooker1();
	 mApiHookerHashMap.insert(make_pair("onSingleTapUpLandroid/widget/Gallery;ZL",onSingleTapUP1));
//	 OnTouchApiHooker* OnTouch = new OnTouchApiHooker();
//	 mApiHookerHashMap.insert(make_pair("onTouchLandroid/support/v4/widget/AutoScrollHelper;ZLL",OnTouch));
//	 onTouchEvent1ApiHooker* onTouchEvent1 = new onTouchEvent1ApiHooker();
//	 mApiHookerHashMap.insert(make_pair("onTouchEvent1Landroid/view/GestureDetector;ZL",onTouchEvent1));
//	 onTouchEventApiHooker* onTouchEvent = new onTouchEventApiHooker();
//	 mApiHookerHashMap.insert(make_pair("onTouchEventLandroid/view/View;ZL",onTouchEvent));
//	 onTouchEventApiHooker10* onTouchEvent10 = new onTouchEventApiHooker10();
//	 mApiHookerHashMap.insert(make_pair("onTouchEventLandroid/app/Dialog;ZL",onTouchEvent10));
//	 onTouchEventApiHooker2* onTouchEvent2 = new onTouchEventApiHooker2();
//	 mApiHookerHashMap.insert(make_pair("onTouchEventLandroid/view/TouchDelegate;ZL",onTouchEvent2));
//	 onTouchEventApiHooker3* onTouchEvent3 = new onTouchEventApiHooker3();
//	 mApiHookerHashMap.insert(make_pair("onTouchEventLandroid/widget/AbsListView;ZL",onTouchEvent3));
//	 onTouchEventApiHooker4* onTouchEvent4 = new onTouchEventApiHooker4();
//	 mApiHookerHashMap.insert(make_pair("onTouchEventLandroid/widget/HorizontalScrollView;ZL",onTouchEvent4));
//	 onTouchEventApiHooker5* onTouchEvent5 = new onTouchEventApiHooker5();
//	 mApiHookerHashMap.insert(make_pair("onTouchEventLandroid/webkit/WebView;ZL",onTouchEvent5));
//	 onTouchEventApiHooker6* onTouchEvent6 = new onTouchEventApiHooker6();
//	 mApiHookerHashMap.insert(make_pair("onTouchEventLandroid/widget/Gallery;ZL",onTouchEvent6));
//	 onTouchEventApiHooker7* onTouchEvent7 = new onTouchEventApiHooker7();
//	 mApiHookerHashMap.insert(make_pair("onTouchEventLandroid/widget/Spinner;ZL",onTouchEvent7));
//	 onTouchEventApiHooker8* onTouchEvent8 = new onTouchEventApiHooker8();
//	 mApiHookerHashMap.insert(make_pair("onTouchEventLandroid/widget/TextView;ZL",onTouchEvent8));
//	 onTouchEventApiHooker9* onTouchEvent9 = new onTouchEventApiHooker9();
//	 mApiHookerHashMap.insert(make_pair("onTouchEventLandroid/app/Activity;ZL",onTouchEvent9));
	 openApiHooker* open = new openApiHooker();
	 mApiHookerHashMap.insert(make_pair("openLandroid/hardware/Camera;LI",open));
	 openConnection1ApiHooker* openConnection1 = new openConnection1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openConnectionLjava/net/URL;L",openConnection1));
	 openConnectionApiHooker* openConnection = new openConnectionApiHooker();
	 mApiHookerHashMap.insert(make_pair("openConnectionLjava/net/URL;LL",openConnection));
	 prepareApiHooker* prepare = new prepareApiHooker();
	 mApiHookerHashMap.insert(make_pair("prepareLandroid/media/MediaRecorder;V",prepare));
	 putExtra1ApiHooker* putExtra1 = new putExtra1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("putExtraLandroid/content/Intent;LLI",putExtra1));
	 putExtra2ApiHooker* putExtra2 = new putExtra2ApiHooker();
	 mApiHookerHashMap.insert(make_pair("putExtraLandroid/content/Intent;LLC",putExtra2));
	 putExtraApiHooker* putExtra = new putExtraApiHooker();
	 mApiHookerHashMap.insert(make_pair("putExtraLandroid/content/Intent;LLD",putExtra));
//	 RectApiHooker* Rect = new RectApiHooker();
//	 mApiHookerHashMap.insert(make_pair("<init>Landroid/graphics/Rect;V",Rect));
	 sendBroadcast2ApiHooker* sendBroadcast2 = new sendBroadcast2ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendBroadcastLandroid/content/ContextWrapper;VLL",sendBroadcast2));
	 sendBroadcastApiHooker* sendBroadcast = new sendBroadcastApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendBroadcastLandroid/content/ContextWrapper;VL",sendBroadcast));
	 sendTextMessageApiHooker* sendTextMessage = new sendTextMessageApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendTextMessageLandroid/telephony/SmsManager;VLLLLL",sendTextMessage));
	 ServiceApiHooker* Service = new ServiceApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/app/Service;V",Service));
//	 setApiHooker* set = new setApiHooker();
//	 mApiHookerHashMap.insert(make_pair("setLandroid/text/TextPaint;VL",set));
	 setOnClickListenerApiHooker* setOnClickListener = new setOnClickListenerApiHooker();
	 mApiHookerHashMap.insert(make_pair("setOnClickListenerLandroid/view/View;VL",setOnClickListener));
//	 setOnClickListenerApiHooker1* setOnClickListener1 = new setOnClickListenerApiHooker1();
//	 mApiHookerHashMap.insert(make_pair("setOnClickListenerLandroid/widget/AutoCompleteTextView;VL",setOnClickListener1));
	 setPackageApiHooker* setPackage = new setPackageApiHooker();
	 mApiHookerHashMap.insert(make_pair("setPackageLandroid/content/Intent;LL",setPackage));
	 SetWifiEnabledWifiManager* SetWifiEnabled= new SetWifiEnabledWifiManager();
	 mApiHookerHashMap.insert(make_pair("setWifiEnabledLandroid/net/wifi/WifiManager;ZZ",SetWifiEnabled));
	 showInputMethodPickerApiHooker* showInputMethodPicker = new showInputMethodPickerApiHooker();
	 mApiHookerHashMap.insert(make_pair("showInputMethodPickerLandroid/view/inputmethod/InputMethodManager;V",showInputMethodPicker));
	 Socket1ApiHooker* Socket1 = new Socket1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Ljava/net/Socket;VL",Socket1));
	 SocketApiHooker* Socket = new SocketApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Ljava/net/Socket;V",Socket));
	 startActivityApiHooker* startActivity = new startActivityApiHooker();
	 mApiHookerHashMap.insert(make_pair("startActivityLandroid/app/Activity;VL",startActivity));
	 startApiHooker* start = new startApiHooker();
	 mApiHookerHashMap.insert(make_pair("startLandroid/media/MediaPlayer;V",start));
	 ThreadApiHooker* Thread = new ThreadApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Ljava/lang/Thread;V",Thread));
	 TranslateAnimationApiHooker* TranslateAnimation = new TranslateAnimationApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/view/animation/TranslateAnimation;VLL",TranslateAnimation));
	 URL1ApiHooker* URL1 = new URL1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Ljava/net/URL;VLL",URL1));
	 URLApiHooker* URL = new URLApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Ljava/net/URL;VL",URL));
	 vApiHooker* v = new vApiHooker();
	 mApiHookerHashMap.insert(make_pair("vLandroid/util/Log;ILL",v));
	 WindowApiHooker* Window = new WindowApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/view/Window;VL",Window));
//	 ZipInputStreamApiHooker* ZipInputStream = new ZipInputStreamApiHooker();
//	 mApiHookerHashMap.insert(make_pair("ZipInputStreamLjava/util/zip;L",ZipInputStream));
//	 ZipOutputStreamApiHooker* ZipOutputStream = new ZipOutputStreamApiHooker();
//	 mApiHookerHashMap.insert(make_pair("ZipOutputStreamLjava/util/zip;L",ZipOutputStream));

*/











	 //第二次
	 accept0ApiHooker* accept0 = new accept0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("acceptLandroid/bluetooth/BluetoothServerSocket;LI",accept0));
	 accept1ApiHooker* accept1 = new accept1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("acceptLjava/net/ServerSocket;L",accept1));
	 acquireDrmInfo0ApiHooker* acquireDrmInfo0 = new acquireDrmInfo0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("acquireDrmInfoLandroid/drm/DrmManagerClient;LL",acquireDrmInfo0));
	 addJavascriptInterface0ApiHooker* addJavascriptInterface0 = new addJavascriptInterface0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("addJavascriptInterfaceLandroid/webkit/WebView;VLL",addJavascriptInterface0));
	 allocateDirect0ApiHooker* allocateDirect0 = new allocateDirect0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("allocateDirectLjava/nio/ByteBuffer;LI",allocateDirect0));
	 append0ApiHooker* append0 = new append0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("appendLjava/lang/StringBuilder;LCII",append0));
	 bulkTransfer0ApiHooker* bulkTransfer0 = new bulkTransfer0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("bulkTransferLandroid/hardware/usb/UsbDeviceConnection;ILBIII",bulkTransfer0));
	 call0ApiHooker* call0 = new call0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("callLandroid/content/ContentProvider;LLLL",call0));
	 call1ApiHooker* call1 = new call1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("callLandroid/content/ContentResolver;LLLLL",call1));
	 capturePicture0ApiHooker* capturePicture0 = new capturePicture0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("capturePictureLandroid/webkit/WebView;L",capturePicture0));
	 CellLocation0ApiHooker* CellLocation0 = new CellLocation0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/telephony/CellLocation;V",CellLocation0));
	 checkAccept0ApiHooker* checkAccept0 = new checkAccept0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("checkAcceptLjava/lang/SecurityManager;VLI",checkAccept0));
	 checkAccess0ApiHooker* checkAccess0 = new checkAccess0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("checkAccessLjava/lang/SecurityManager;VL",checkAccess0));
	 checkConnect0ApiHooker* checkConnect0 = new checkConnect0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("checkConnectLjava/lang/SecurityManager;VLIL",checkConnect0));
	 checkLink0ApiHooker* checkLink0 = new checkLink0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("checkLinkLjava/lang/SecurityManager;VL",checkLink0));
	 checkPermission0ApiHooker* checkPermission0 = new checkPermission0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("checkPermissionLjava/lang/SecurityManager;VLL",checkPermission0));
	 checkRead0ApiHooker* checkRead0 = new checkRead0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("checkReadLjava/lang/SecurityManager;VL",checkRead0));
	 checkSecurityAccess0ApiHooker* checkSecurityAccess0 = new checkSecurityAccess0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("checkSecurityAccessLjava/lang/SecurityManager;VL",checkSecurityAccess0));
	 checkWrite0ApiHooker* checkWrite0 = new checkWrite0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("checkWriteLjava/lang/SecurityManager;VL",checkWrite0));
	 claimInterface0ApiHooker* claimInterface0 = new claimInterface0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("claimInterfaceLandroid/hardware/usb/UsbDeviceConnection;ZLZ",claimInterface0));
	 clearApplicationUserData0ApiHooker* clearApplicationUserData0 = new clearApplicationUserData0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("clearApplicationUserDataLandroid/app/ActivityManager;Z",clearApplicationUserData0));
	 close0ApiHooker* close0 = new close0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("closeLjava/net/Socket;V",close0));
	 connect0ApiHooker* connect0 = new connect0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("connectLandroid/bluetooth/BluetoothSocket;V",connect0));
	 connect1ApiHooker* connect1 = new connect1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("connectLjava/net/Socket;VLI",connect1));
	 connectGatt0ApiHooker* connectGatt0 = new connectGatt0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("connectGattLandroid/bluetooth/BluetoothDevice;LLZL",connectGatt0));
	 convertData0ApiHooker* convertData0 = new convertData0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("convertDataLandroid/drm/DrmManagerClient;LIB",convertData0));
	 create0ApiHooker* create0 = new create0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("createLandroid/media/MediaPlayer;LLL",create0));
	 create1ApiHooker* create1 = new create1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("createLjava/net/URI;LL",create1));
	 create2ApiHooker* create2 = new create2ApiHooker();
	 mApiHookerHashMap.insert(make_pair("createLandroid/database/sqlite/SQLiteDatabase;LL",create2));
	 createNewFile0ApiHooker* createNewFile0 = new createNewFile0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("createNewFileLjava/io/File;Z",createNewFile0));
	 createSSLEngine0ApiHooker* createSSLEngine0 = new createSSLEngine0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("createSSLEngineLjavax/net/ssl/SSLContext;L",createSSLEngine0));
	 currentTimeMillis0ApiHooker* currentTimeMillis0 = new currentTimeMillis0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("currentTimeMillisLjava/lang/System;J",currentTimeMillis0));
	 databaseList0ApiHooker* databaseList0 = new databaseList0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("databaseListLandroid/content/ContextWrapper;L",databaseList0));
	 decode0ApiHooker* decode0 = new decode0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("decodeLandroid/util/Base64;BLI",decode0));
	 decodeStream0ApiHooker* decodeStream0 = new decodeStream0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("decodeStreamLandroid/graphics/BitmapFactory;LL",decodeStream0));
	 delete0ApiHooker* delete0 = new delete0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("deleteLjava/io/File;Z",delete0));
	 delete1ApiHooker* delete1 = new delete1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("deleteLandroid/database/sqlite/SQLiteDatabase;ILLL",delete1));
	 deleteDatabase0ApiHooker* deleteDatabase0 = new deleteDatabase0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("deleteDatabaseLandroid/content/ContextWrapper;ZL",deleteDatabase0));
	 deleteDatabase1ApiHooker* deleteDatabase1 = new deleteDatabase1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("deleteDatabaseLandroid/database/sqlite/SQLiteDatabase;ZL",deleteDatabase1));
	 deleteFile0ApiHooker* deleteFile0 = new deleteFile0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("deleteFileLandroid/content/ContextWrapper;ZL",deleteFile0));
	 directory0ApiHooker* directory0 = new directory0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("directoryLjava/lang/ProcessBuilder;LL",directory0));
	 disableForegroundDispatch0ApiHooker* disableForegroundDispatch0 = new disableForegroundDispatch0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("disableForegroundDispatchLandroid/nfc/NfcAdapter;VL",disableForegroundDispatch0));
//	 点击没有反应
//	 dispatchTouchEvent0ApiHooker* dispatchTouchEvent0 = new dispatchTouchEvent0ApiHooker();
//	 mApiHookerHashMap.insert(make_pair("dispatchTouchEventLandroid/view/ViewGroup;ZL",dispatchTouchEvent0));
//	 dispatchTouchEvent1ApiHooker* dispatchTouchEvent1 = new dispatchTouchEvent1ApiHooker();
//	 mApiHookerHashMap.insert(make_pair("dispatchTouchEventLandroid/widget/LinearLayout;ZL",dispatchTouchEvent1));
//	 draw0ApiHooker* draw0 = new draw0ApiHooker();
//	 mApiHookerHashMap.insert(make_pair("drawLandroid/view/View;VL",draw0));
	 enableReaderMode0ApiHooker* enableReaderMode0 = new enableReaderMode0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("enableReaderModeLandroid/nfc/NfcAdapter;VLLIL",enableReaderMode0));
	 encode0ApiHooker* encode0 = new encode0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("encodeLandroid/util/Base64;BBI",encode0));
	 equals0ApiHooker* equals0 = new equals0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("equalsLjava/lang/reflect/Method;ZL",equals0));
	 execSQL0ApiHooker* execSQL0 = new execSQL0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("execSQLLandroid/database/sqlite/SQLiteDatabase;VL",execSQL0));
	 execute0ApiHooker* execute0 = new execute0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("executeLorg/apache/http/impl/client/AbstractHttpClient;LL",execute0));
	 execute1ApiHooker* execute1 = new execute1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("executeLjava/util/concurrent/ScheduledThreadPoolExecutor;VL",execute1));
	 fileList0ApiHooker* fileList0 = new fileList0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("fileListLandroid/content/ContextWrapper;L",fileList0));
	 findAddress0ApiHooker* findAddress0 = new findAddress0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("findAddressLandroid/webkit/WebView;LL",findAddress0));
	 findResource0ApiHooker* findResource0 = new findResource0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("findResourceLjava/lang/ClassLoader;LL",findResource0));
	 get0ApiHooker* get0 = new get0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getLjava/lang/reflect/Field;LL",get0));
	 getAccessoryList0ApiHooker* getAccessoryList0 = new getAccessoryList0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getAccessoryListLandroid/hardware/usb/UsbManager;L",getAccessoryList0));
	 getAction0ApiHooker* getAction0 = new getAction0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getActionLandroid/content/Intent;L",getAction0));
	 //卡,没反应
//	 getAction1ApiHooker* getAction1 = new getAction1ApiHooker();
//	 mApiHookerHashMap.insert(make_pair("getActionLandroid/view/MotionEvent;I",getAction1));
	 getAddress0ApiHooker* getAddress0 = new getAddress0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getAddressLandroid/bluetooth/BluetoothDevice;L",getAddress0));
	 getApplicationContext0ApiHooker* getApplicationContext0 = new getApplicationContext0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getApplicationContextLandroid/content/ContextWrapper;L",getApplicationContext0));
	 getAssets0ApiHooker* getAssets0 = new getAssets0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getAssetsLandroid/content/res/Resources;L",getAssets0));
	 getBoolean0ApiHooker* getBoolean0 = new getBoolean0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getBooleanLjava/lang/reflect/Field;ZL",getBoolean0));
	 getBoolean1ApiHooker* getBoolean1 = new getBoolean1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getBooleanLandroid/content/res/Resources;ZI",getBoolean1));
	 getByte0ApiHooker* getByte0 = new getByte0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getByteLjava/lang/reflect/Field;BL",getByte0));
	 getCellLocation0ApiHooker* getCellLocation0 = new getCellLocation0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getCellLocationLandroid/telephony/TelephonyManager;L",getCellLocation0));
	 getCertificate0ApiHooker* getCertificate0 = new getCertificate0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getCertificateLjava/security/KeyStore;LL",getCertificate0));
	 getCertificate1ApiHooker* getCertificate1 = new getCertificate1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getCertificateLandroid/webkit/WebView;L",getCertificate1));
	 getChar0ApiHooker* getChar0 = new getChar0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getCharLjava/lang/reflect/Field;CL",getChar0));
	 getClassLoader0ApiHooker* getClassLoader0 = new getClassLoader0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getClassLoaderLjava/lang/Class;L",getClassLoader0));
	 getColumnIndex0ApiHooker* getColumnIndex0 = new getColumnIndex0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getColumnIndexLandroid/database/CursorWrapper;IL",getColumnIndex0));
	 getColumnIndex1ApiHooker* getColumnIndex1 = new getColumnIndex1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getColumnIndexLandroid/database/sqlite/SQLiteCursor;IL",getColumnIndex1));
	 getColumnNames0ApiHooker* getColumnNames0 = new getColumnNames0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getColumnNamesLandroid/database/sqlite/SQLiteCursor;L",getColumnNames0));
	 getContent0ApiHooker* getContent0 = new getContent0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getContentLjava/net/URL;L",getContent0));
	 getCookiesStore0ApiHooker* getCookiesStore0 = new getCookiesStore0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getCookieStoreLorg/apache/http/impl/client/AbstractHttpClient;L",getCookiesStore0));
	 getCredentialProvider0ApiHooker* getCredentialProvider0 = new getCredentialProvider0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getCredentialsProviderLorg/apache/http/impl/client/AbstractHttpClient;L",getCredentialProvider0));
	 getData0ApiHooker* getData0 = new getData0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDataLandroid/content/Intent;L",getData0));
	 getDatabase0ApiHooker* getDatabase0 = new getDatabase0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDatabaseLandroid/database/sqlite/SQLiteCursor;L",getDatabase0));
	 getDatabasePath0ApiHooker* getDatabasePath0 = new getDatabasePath0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDatabasePathLandroid/content/ContextWrapper;LL",getDatabasePath0));
	 getDeclaredConstructors0ApiHooker* getDeclaredConstructors0 = new getDeclaredConstructors0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDeclaredConstructorsLjava/lang/Class;L",getDeclaredConstructors0));
//	 getDeclaredFields0ApiHooker* getDeclaredFields0 = new getDeclaredFields0ApiHooker();
//	 mApiHookerHashMap.insert(make_pair("getDeclaredFieldLjava/lang/Class;LL",getDeclaredFields0));
	 getDeclaredMethods0ApiHooker* getDeclaredMethods0 = new getDeclaredMethods0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDeclaredMethodsLjava/lang/Class;L",getDeclaredMethods0));
	 getDefault0ApiHooker* getDefault0 = new getDefault0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDefaultLjavax/net/ssl/SSLContext;L",getDefault0));
	 getDefault1ApiHooker* getDefault1 = new getDefault1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDefaultLandroid/net/SSLCertificateSocketFactory;LIL",getDefault1));
	 getDefaultHostnameVerifier0ApiHooker* getDefaultHostnameVerifier0 = new getDefaultHostnameVerifier0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDefaultHostnameVerifierLjavax/net/ssl/HttpsURLConnection;L",getDefaultHostnameVerifier0));
	 getDefaultSSLSocketFactory0ApiHooker* getDefaultSSLSocketFactory0 = new getDefaultSSLSocketFactory0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDefaultSSLSocketFactoryLjavax/net/ssl/HttpsURLConnection;L",getDefaultSSLSocketFactory0));
	 getDeviceConfigurationInfo0ApiHooker* getDeviceConfigurationInfo0 = new getDeviceConfigurationInfo0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDeviceConfigurationInfoLandroid/app/ActivityManager;L",getDeviceConfigurationInfo0));
	 getDir0ApiHooker* getDir0 = new getDir0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDirLandroid/content/ContextWrapper;LLI",getDir0));
	 getDisplayMessageBody0ApiHooker* getDisplayMessageBody0 = new getDisplayMessageBody0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDisplayMessageBodyLandroid/telephony/SmsMessage;L",getDisplayMessageBody0));
	 getDisplayOriginatingAddress0ApiHooker* getDisplayOriginatingAddress0 = new getDisplayOriginatingAddress0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDisplayOriginatingAddressLandroid/telephony/SmsMessage;L",getDisplayOriginatingAddress0));
	 getDouble0ApiHooker* getDouble0 = new getDouble0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getDoubleLjava/lang/reflect/Field;DL",getDouble0));
	 getExternalFilesDir0ApiHooker* getExternalFilesDir0 = new getExternalFilesDir0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getExternalFilesDirLandroid/content/ContextWrapper;LL",getExternalFilesDir0));
	 getField0ApiHooker* getField0 = new getField0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getFieldLjava/lang/Class;LL",getField0));
	 getFields0ApiHooker* getFields0 = new getFields0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getFieldsLjava/lang/Class;L",getFields0));
	 getFile0ApiHooker* getFile0 = new getFile0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getFileLjava/net/URL;L",getFile0));
	 getFilesDir0ApiHooker* getFilesDir0 = new getFilesDir0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getFilesDirLandroid/content/ContextWrapper;L",getFilesDir0));
	 getFileStreamPath0ApiHooker* getFileStreamPath0 = new getFileStreamPath0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getFileStreamPathLandroid/content/ContextWrapper;LL",getFileStreamPath0));
	 getFloat0ApiHooker* getFloat0 = new getFloat0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getFloatLjava/lang/reflect/Field;FL",getFloat0));
	 getHeaderFieldDate0ApiHooker* getHeaderFieldDate0 = new getHeaderFieldDate0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getHeaderFieldDateLjava/net/HttpURLConnection;JLJ",getHeaderFieldDate0));
	 getHostnameVerifier0ApiHooker* getHostnameVerifier0 = new getHostnameVerifier0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getHostnameVerifierLjavax/net/ssl/HttpsURLConnection;L",getHostnameVerifier0));
	 getIndexOnSim0ApiHooker* getIndexOnSim0 = new getIndexOnSim0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getIndexOnSimLandroid/telephony/SmsMessage;I",getIndexOnSim0));
	 getInstance0ApiHooker* getInstance0 = new getInstance0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getInstanceLjavax/net/ssl/SSLContext;LL",getInstance0));
	 getInstance1ApiHooker* getInstance1 = new getInstance1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getInstanceLjavax/net/ssl/KeyManagerFactory;LLL",getInstance1));
	 getInstance2ApiHooker* getInstance2 = new getInstance2ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getInstanceLjavax/crypto/Cipher;LL",getInstance2));
	 getInstance3ApiHooker* getInstance3 = new getInstance3ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getInstanceLjava/security/MessageDigest;LL",getInstance3));
	 getInt0ApiHooker* getInt0 = new getInt0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getIntLjava/lang/reflect/Field;IL",getInt0));
	 getKey0ApiHooker* getKey0 = new getKey0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getKeyLjava/security/KeyStore;LLC",getKey0));
	 getLastKnownLocation0ApiHooker* getLastKnownLocation0 = new getLastKnownLocation0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getLastKnownLocationLandroid/location/LocationManager;LL",getLastKnownLocation0));
	 getLatitude0ApiHooker* getLatitude0 = new getLatitude0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getLatitudeLandroid/location/Location;D",getLatitude0));
	 getLocalAddress0ApiHooker* getLocalAddress0 = new getLocalAddress0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getLocalAddressLjava/net/Socket;L",getLocalAddress0));
	 getLocalPort0ApiHooker* getLocalPort0 = new getLocalPort0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getLocalPortLjava/net/Socket;I",getLocalPort0));
	 getLocalPrincipal0ApiHooker* getLocalPrincipal0 = new getLocalPrincipal0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getLocalPrincipalLjavax/net/ssl/HttpsURLConnection;L",getLocalPrincipal0));
	 getLong0ApiHooker* getLong0 = new getLong0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getLongLjava/lang/reflect/Field;JL",getLong0));
	 getMemoryInfo0ApiHooker* getMemoryInfo0 = new getMemoryInfo0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getMemoryInfoLandroid/app/ActivityManager;VL",getMemoryInfo0));
	 getMetadata0ApiHooker* getMetadata0 = new getMetadata0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getMetadataLandroid/drm/DrmManagerClient;LL",getMetadata0));
	 getNetworkOperator0ApiHooker* getNetworkOperator0 = new getNetworkOperator0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getNetworkOperatorLandroid/telephony/TelephonyManager;L",getNetworkOperator0));
	 getOperatorAlphaLong0ApiHooker* getOperatorAlphaLong0 = new getOperatorAlphaLong0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getOperatorAlphaLongLandroid/telephony/ServiceState;L",getOperatorAlphaLong0));
	 getOperatorAlphaShort0ApiHooker* getOperatorAlphaShort0 = new getOperatorAlphaShort0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getOperatorAlphaShortLandroid/telephony/ServiceState;L",getOperatorAlphaShort0));
	 getOutputStream0ApiHooker* getOutputStream0 = new getOutputStream0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getOutputStreamLjava/net/Socket;L",getOutputStream0));
	 getPackage0ApiHooker* getPackage0 = new getPackage0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getPackageLjava/lang/Class;L",getPackage0));
	 getParams0ApiHooker* getParams0 = new getParams0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getParamsLorg/apache/http/impl/client/AbstractHttpClient;L",getParams0));
	 getPath0ApiHooker* getPath0 = new getPath0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getPathLjava/net/URL;L",getPath0));
	 getPathPermissions0ApiHooker* getPathPermissions0 = new getPathPermissions0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getPathPermissionsLandroid/content/ContentProvider;L",getPathPermissions0));
	 getPermission0ApiHooker* getPermission0 = new getPermission0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getPermissionLjava/net/HttpURLConnection;L",getPermission0));
	 getPort0ApiHooker* getPort0 = new getPort0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getPortLjava/net/Socket;I",getPort0));
	 getPosition0ApiHooker* getPosition0 = new getPosition0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getPositionLandroid/database/CursorWrapper;I",getPosition0));
	 getProtocol0ApiHooker* getProtocol0 = new getProtocol0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getProtocolLjava/net/URL;L",getProtocol0));
	 getReadPermission0ApiHooker* getReadPermission0 = new getReadPermission0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getReadPermissionLandroid/content/ContentProvider;L",getReadPermission0));
	 getResource0ApiHooker* getResource0 = new getResource0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getResourceLjava/lang/Class;LL",getResource0));
	 getResource1ApiHooker* getResource1 = new getResource1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getResourceLjava/lang/ClassLoader;LL",getResource1));
	 getResourceAsStream0ApiHooker* getResourceAsStream0 = new getResourceAsStream0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getResourceAsStreamLjava/lang/ClassLoader;LL",getResourceAsStream0));
	 //ka?
//	 getResourceName0ApiHooker* getResourceName0 = new getResourceName0ApiHooker();
//	 mApiHookerHashMap.insert(make_pair("getResourceNameLandroid/content/res/Resources;LI",getResourceName0));
	 getResourcePackageName0ApiHooker* getResourcePackageName0 = new getResourcePackageName0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getResourcePackageNameLandroid/content/res/Resources;LI",getResourcePackageName0));
	 getRootDirectory0ApiHooker* getRootDirectory0 = new getRootDirectory0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getRootDirectoryLandroid/os/Environment;L",getRootDirectory0));
	 getSerial0ApiHooker* getSerial0 = new getSerial0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getSerialLandroid/hardware/usb/UsbDeviceConnection;L",getSerial0));
	 getServiceCenterAddress0ApiHooker* getServiceCenterAddress0 = new getServiceCenterAddress0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getServiceCenterAddressLandroid/telephony/SmsMessage;L",getServiceCenterAddress0));
	 getSimOperator0ApiHooker* getSimOperator0 = new getSimOperator0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getSimOperatorLandroid/telephony/TelephonyManager;L",getSimOperator0));
	 getSnr0ApiHooker* getSnr0 = new getSnr0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getSnrLandroid/location/GpsSatellite;F",getSnr0));
	 getStatus0ApiHooker* getStatus0 = new getStatus0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getStatusLandroid/telephony/SmsMessage;I",getStatus0));
	 getStatusOnSim0ApiHooker* getStatusOnSim0 = new getStatusOnSim0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getStatusOnSimLandroid/telephony/SmsMessage;I",getStatusOnSim0));
	 getString0ApiHooker* getString0 = new getString0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getStringLandroid/content/res/Resources;LI",getString0));
	 getSubscriberId0ApiHooker* getSubscriberId0 = new getSubscriberId0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getSubscriberIdLandroid/telephony/TelephonyManager;L",getSubscriberId0));
	 getSystem0ApiHooker* getSystem0 = new getSystem0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getSystemLandroid/content/res/Resources;L",getSystem0));
	 getSystemResource0ApiHooker* getSystemResource0 = new getSystemResource0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getSystemResourceLjava/lang/ClassLoader;LL",getSystemResource0));
	 getSystemService0ApiHooker* getSystemService0 = new getSystemService0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getSystemServiceLandroid/app/Activity;LL",getSystemService0));
	 getUserData0ApiHooker* getUserData0 = new getUserData0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getUserDataLandroid/accounts/AccountManager;LLL",getUserData0));
	 getUserData1ApiHooker* getUserData1 = new getUserData1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getUserDataLandroid/telephony/SmsMessage;B",getUserData1));
	 getWritePermission0ApiHooker* getWritePermission0 = new getWritePermission0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("getWritePermissionLandroid/content/ContentProvider;L",getWritePermission0));
	 GLSurfaceView0ApiHooker* GLSurfaceView0 = new GLSurfaceView0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/opengl/GLSurfaceView;VL",GLSurfaceView0));
	 hasAccuracy0ApiHooker* hasAccuracy0 = new hasAccuracy0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("hasAccuracyLandroid/location/Location;Z",hasAccuracy0));
	 HttpGet0ApiHooker* HttpGet0 = new HttpGet0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Lorg/apache/http/client/methods/HttpGet;V",HttpGet0));
	 init0ApiHooker* init0 = new init0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("initLjavax/net/ssl/KeyManagerFactory;VL",init0));
	 init1ApiHooker* init1 = new init1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("initLjavax/crypto/Mac;VL",init1));
	 init2ApiHooker* init2 = new init2ApiHooker();
	 mApiHookerHashMap.insert(make_pair("initLjavax/net/ssl/SSLContext;VLLL",init2));
	 insert0ApiHooker* insert0 = new insert0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("insertLandroid/content/ContentResolver;LLL",insert0));
	 insertWithOnConflict0ApiHooker* insertWithOnConflict0 = new insertWithOnConflict0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("insertWithOnConflictLandroid/database/sqlite/SQLiteDatabase;JLLLI",insertWithOnConflict0));
//	 IOException0ApiHooker* IOException0 = new IOException0ApiHooker();
//	 mApiHookerHashMap.insert(make_pair("<init>Ljava/io/IOException;V",IOException0));
	 isEnabled0ApiHooker* isEnabled0 = new isEnabled0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("isEnabledLandroid/nfc/NfcAdapter;Z",isEnabled0));
	 //部分情况卡死
//	 isInstance0ApiHooker* isInstance0 = new isInstance0ApiHooker();
//	 mApiHookerHashMap.insert(make_pair("isInstanceLjava/lang/Class;ZL",isInstance0));
	 isSpeakerphoneOn0ApiHooker* isSpeakerphoneOn0 = new isSpeakerphoneOn0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("isSpeakerphoneOnLandroid/media/AudioManager;Z",isSpeakerphoneOn0));
	 list0ApiHooker* list0 = new list0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("listLjava/io/File;L",list0));
	 listFiles0ApiHooker* listFiles0 = new listFiles0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("listFilesLjava/io/File;L",listFiles0));
	 load0ApiHooker* load0 = new load0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("loadLjava/security/KeyStore;VL",load0));
	 loadData0ApiHooker* loadData0 = new loadData0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("loadDataLandroid/webkit/WebView;VLLL",loadData0));
	 loadDataWithBaseURL0ApiHooker* loadDataWithBaseURL0 = new loadDataWithBaseURL0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("loadDataWithBaseURLLandroid/webkit/WebView;VLLLLL",loadDataWithBaseURL0));
	 mkdirs0ApiHooker* mkdirs0 = new mkdirs0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("mkdirsLjava/io/File;Z",mkdirs0));
	 nextFloat0ApiHooker* nextFloat0 = new nextFloat0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("nextFloatLjava/util/Random;F",nextFloat0));
	 onCreate0ApiHooker* onCreate0 = new onCreate0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("onCreateLandroid/app/Service;V",onCreate0));
	 onMove0ApiHooker* onMove0 = new onMove0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("onMoveLandroid/database/sqlite/SQLiteCursor;ZII",onMove0));
	 openAccessory0ApiHooker* openAccessory0 = new openAccessory0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openAccessoryLandroid/hardware/usb/UsbManager;LL",openAccessory0));
	 openAssetFileDescriptor0ApiHooker* openAssetFileDescriptor0 = new openAssetFileDescriptor0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openAssetFileDescriptorLandroid/content/ContentResolver;LLL",openAssetFileDescriptor0));
	 openDatabase0ApiHooker* openDatabase0 = new openDatabase0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openDatabaseLandroid/database/sqlite/SQLiteDatabase;LLLI",openDatabase0));
	 openDevice0ApiHooker* openDevice0 = new openDevice0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openDeviceLandroid/hardware/usb/UsbManager;LL",openDevice0));
	 openFile0ApiHooker* openFile0 = new openFile0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openFileLandroid/content/ContentProvider;LLL",openFile0));
	 openFileDescriptor0ApiHooker* openFileDescriptor0 = new openFileDescriptor0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openFileDescriptorLandroid/content/ContentResolver;LLL",openFileDescriptor0));
	 openFileInput0ApiHooker* openFileInput0 = new openFileInput0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openFileInputLandroid/content/ContextWrapper;LL",openFileInput0));
	 openFileOutput0ApiHooker* openFileOutput0 = new openFileOutput0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openFileOutputLandroid/content/ContextWrapper;LLI",openFileOutput0));
	 openInputStream0ApiHooker* openInputStream0 = new openInputStream0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openInputStreamLandroid/content/ContentResolver;LL",openInputStream0));
	 openOrCreateDatabase0ApiHooker* openOrCreateDatabase0 = new openOrCreateDatabase0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openOrCreateDatabaseLandroid/content/ContextWrapper;LLIL",openOrCreateDatabase0));
	 openOrCreateDatabase1ApiHooker* openOrCreateDatabase1 = new openOrCreateDatabase1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openOrCreateDatabaseLandroid/database/sqlite/SQLiteDatabase;LLL",openOrCreateDatabase1));
	 openOutputStream0ApiHooker* openOutputStream0 = new openOutputStream0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openOutputStreamLandroid/content/ContentResolver;LL",openOutputStream0));
	 openRawResource0ApiHooker* openRawResource0 = new openRawResource0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openRawResourceLandroid/content/res/Resources;LIL",openRawResource0));
	 openRawResource1ApiHooker* openRawResource1 = new openRawResource1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("openRawResourceLandroid/content/res/Resources;LI",openRawResource1));
	 order0ApiHooker* order0 = new order0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("orderLjava/nio/ByteBuffer;L",order0));
	 parseBundleExtraparseBundleExtra0ApiHooker* parseBundleExtraparseBundleExtra0 = new parseBundleExtraparseBundleExtra0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("parseBundleExtraLandroid/content/res/Resources;VLLL",parseBundleExtraparseBundleExtra0));
	 parseBundleExtras0ApiHooker* parseBundleExtras0 = new parseBundleExtras0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("parseBundleExtrasLandroid/content/res/Resources;VLL",parseBundleExtras0));
	 parseUri0ApiHooker* parseUri0 = new parseUri0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("parseUriLandroid/content/Intent;LLI",parseUri0));
	 Proxy0ApiHooker* Proxy0 = new Proxy0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Ljava/net/Proxy;V",Proxy0));
	 purge0ApiHooker* purge0 = new purge0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("purgeLjava/util/Timer;I",purge0));
	 query0ApiHooker* query0 = new query0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("queryLandroid/database/sqlite/SQLiteDatabase;LLLLLLLL",query0));
	 queryWithFactory0ApiHooker* queryWithFactory0 = new queryWithFactory0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("queryWithFactoryLandroid/database/sqlite/SQLiteDatabase;LLZLLLLLLLL",queryWithFactory0));
	 rawQuery0ApiHooker* rawQuery0 = new rawQuery0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("rawQueryLandroid/database/sqlite/SQLiteDatabase;LLL",rawQuery0));
	 read0ApiHooker* read0 = new read0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("readLandroid/media/AudioRecord;ILI",read0));
	 recycle0ApiHooker* recycle0 = new recycle0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("recycleLandroid/graphics/Bitmap;V",recycle0));
	 registerMediaButtonEventReceiver0ApiHooker* registerMediaButtonEventReceiver0 = new registerMediaButtonEventReceiver0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("registerMediaButtonEventReceiverLandroid/media/AudioManager;VL",registerMediaButtonEventReceiver0));
	 registerRemoteControlClient0ApiHooker* registerRemoteControlClient0 = new registerRemoteControlClient0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("registerRemoteControlClientLandroid/media/AudioManager;VL",registerRemoteControlClient0));
	 replace0ApiHooker* replace0 = new replace0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("replaceLandroid/database/sqlite/SQLiteDatabase;JLLL",replace0));
	 replaceOrThrow0ApiHooker* replaceOrThrow0 = new replaceOrThrow0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("replaceOrThrowLandroid/database/sqlite/SQLiteDatabase;JLLL",replaceOrThrow0));
	 requestPermission0ApiHooker* requestPermission0 = new requestPermission0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("requestPermissionLandroid/hardware/usb/UsbManager;VLL",requestPermission0));
	 Resources0ApiHooker* Resources0 = new Resources0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/content/res/Resources;VLLL",Resources0));
	 respond0ApiHooker* respond0 = new respond0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("respondLandroid/database/CursorWrapper;LL",respond0));
	 restartPackage0ApiHooker* restartPackage0 = new restartPackage0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("restartPackageLandroid/app/ActivityManager;VL",restartPackage0));
	 saveRights0ApiHooker* saveRights0 = new saveRights0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("saveRightsLandroid/drm/DrmManagerClient;ILLL",saveRights0));
	 schedule0ApiHooker* schedule0 = new schedule0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("scheduleLjava/util/Timer;VLL",schedule0));
	 sendDataMessage0ApiHooker* sendDataMessage0 = new sendDataMessage0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendDataMessageLandroid/telephony/SmsManager;VLLSBLL",sendDataMessage0));
	 sendTextMessage0ApiHooker* sendTextMessage0 = new sendTextMessage0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("sendTextMessageLandroid/telephony/SmsManager;VLLLLL",sendTextMessage0));
	 ServerSocket0ApiHooker* ServerSocket0 = new ServerSocket0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Ljava/net/ServerSocket;V",ServerSocket0));
	 set0ApiHooker* set0 = new set0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setLjava/lang/reflect/Field;VLL",set0));
	 setAction0ApiHooker* setAction0 = new setAction0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setActionLandroid/content/Intent;LL",setAction0));
	 setAllowContentAccess0ApiHooker* setAllowContentAccess0 = new setAllowContentAccess0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setAllowContentAccessLandroid/webkit/WebSettings;VZ",setAllowContentAccess0));
	 setAllowFileAccess0ApiHooker* setAllowFileAccess0 = new setAllowFileAccess0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setAllowFileAccessLandroid/webkit/WebSettings;VZ",setAllowFileAccess0));
	 setAltitude0ApiHooker* setAltitude0 = new setAltitude0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setAltitudeLandroid/location/Location;VD",setAltitude0));
	 setBeamPushUris0ApiHooker* setBeamPushUris0 = new setBeamPushUris0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setBeamPushUrisLandroid/nfc/NfcAdapter;VLL",setBeamPushUris0));
	 setBoolean0ApiHooker* setBoolean0 = new setBoolean0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setBooleanLjava/lang/reflect/Field;VLZ",setBoolean0));
	 setByte0ApiHooker* setByte0 = new setByte0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setByteLjava/lang/reflect/Field;VLB",setByte0));
	 setChar0ApiHooker* setChar0 = new setChar0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setCharLjava/lang/reflect/Field;VLC",setChar0));
	 setContentView0ApiHooker* setContentView0 = new setContentView0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setContentViewLandroid/app/Activity;VL",setContentView0));
	 setData0ApiHooker* setData0 = new setData0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setDataLandroid/content/Intent;LL",setData0));
	 setDatabasePath0ApiHooker* setDatabasePath0 = new setDatabasePath0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setDatabasePathLandroid/webkit/WebSettings;VL",setDatabasePath0));
	 setDefaultHostnameVerifier0ApiHooker* setDefaultHostnameVerifier0 = new setDefaultHostnameVerifier0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setDefaultHostnameVerifierLjavax/net/ssl/HttpsURLConnection;VL",setDefaultHostnameVerifier0));
	 setDefaultSSLSocketFactory0ApiHooker* setDefaultSSLSocketFactory0 = new setDefaultSSLSocketFactory0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setDefaultSSLSocketFactoryLjavax/net/ssl/HttpsURLConnection;VL",setDefaultSSLSocketFactory0));
	 setDouble0ApiHooker* setDouble0 = new setDouble0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setDoubleLjava/lang/reflect/Field;VLD",setDouble0));
	 setFloat0ApiHooker* setFloat0 = new setFloat0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setFloatLjava/lang/reflect/Field;VLF",setFloat0));
	 setHostname0ApiHooker* setHostname0 = new setHostname0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setHostnameLandroid/net/SSLCertificateSocketFactory;VLL",setHostname0));
	 setHostnameVerifier0ApiHooker* setHostnameVerifier0 = new setHostnameVerifier0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setHostnameVerifierLjavax/net/ssl/HttpsURLConnection;VL",setHostnameVerifier0));
	 setInt0ApiHooker* setInt0 = new setInt0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setIntLjava/lang/reflect/Field;VLI",setInt0));
	 setLatitude0ApiHooker* setLatitude0 = new setLatitude0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setLatitudeLandroid/location/Location;VD",setLatitude0));
	 setLocation0ApiHooker* setLocation0 = new setLocation0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setLocationLandroid/media/MediaRecorder;VFF",setLocation0));
	 setLong0ApiHooker* setLong0 = new setLong0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setLongLjava/lang/reflect/Field;VLJ",setLong0));
	 //hook时找不到方法
//	 setNdefPushMessage0ApiHooker* setNdefPushMessage0 = new setNdefPushMessage0ApiHooker();
//	 mApiHookerHashMap.insert(make_pair("setNdefPushMessageLandroid/nfc/NfcAdapter;VLL",setNdefPushMessage0));
	 setNpnProtocolssetNpnProtocols0ApiHooker* setNpnProtocolssetNpnProtocols0 = new setNpnProtocolssetNpnProtocols0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setNpnProtocolsLandroid/net/SSLCertificateSocketFactory;VB",setNpnProtocolssetNpnProtocols0));
	 setOutputFile0ApiHooker* setOutputFile0 = new setOutputFile0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setOutputFileLandroid/media/MediaRecorder;VL",setOutputFile0));
	 setPackageAssertionStatus0ApiHooker* setPackageAssertionStatus0 = new setPackageAssertionStatus0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setPackageAssertionStatusLjava/lang/ClassLoader;VLZ",setPackageAssertionStatus0));
	 setParameters0ApiHooker* setParameters0 = new setParameters0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setParametersLandroid/media/AudioManager;VL",setParameters0));
	 setProtocols0ApiHooker* setProtocols0 = new setProtocols0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setProtocolsLjavax/net/ssl/SSLParameters;VL",setProtocols0));
	 setRoaming0ApiHooker* setRoaming0 = new setRoaming0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setRoamingLandroid/telephony/ServiceState;VZ",setRoaming0));
	 setSocketImplFactory0ApiHooker* setSocketImplFactory0 = new setSocketImplFactory0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setSocketImplFactoryLjava/net/Socket;VL",setSocketImplFactory0));
	 setSpeakerphoneOn0ApiHooker* setSpeakerphoneOn0 = new setSpeakerphoneOn0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setSpeakerphoneOnLandroid/media/AudioManager;VZ",setSpeakerphoneOn0));
	 setSSLSocketFactory0ApiHooker* setSSLSocketFactory0 = new setSSLSocketFactory0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setSSLSocketFactoryLjavax/net/ssl/HttpsURLConnection;VL",setSSLSocketFactory0));
	 setState0ApiHooker* setState0 = new setState0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setStateLandroid/telephony/ServiceState;VI",setState0));
	 setStateOutOfService0ApiHooker* setStateOutOfService0 = new setStateOutOfService0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setStateOutOfServiceLandroid/telephony/ServiceState;V",setStateOutOfService0));
	 setWindow0ApiHooker* setWindow0 = new setWindow0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setWindowLandroid/database/sqlite/SQLiteCursor;VL",setWindow0));
	 setWritable0ApiHooker* setWritable0 = new setWritable0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("setWritableLjava/io/File;ZZ",setWritable0));
	 shutdown0ApiHooker* shutdown0 = new shutdown0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("shutdownLjava/util/concurrent/ScheduledThreadPoolExecutor;V",shutdown0));
	 shutdownInput0ApiHooker* shutdownInput0 = new shutdownInput0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("shutdownInputLjava/net/Socket;V",shutdownInput0));
	 shutdownOutput0ApiHooker* shutdownOutput0 = new shutdownOutput0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("shutdownOutputLjava/net/Socket;V",shutdownOutput0));
	 SSKOarameters0ApiHooker* SSKOarameters0 = new SSKOarameters0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Ljavax/net/ssl/SSLParameters;V",SSKOarameters0));
	 SSLCertificateSocketFactory0ApiHooker* SSLCertificateSocketFactory0 = new SSLCertificateSocketFactory0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Landroid/net/SSLCertificateSocketFactory;VI",SSLCertificateSocketFactory0));
	 start0ApiHooker* start0 = new start0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("startLjava/lang/ProcessBuilder;L",start0));
	 startActivities0ApiHooker* startActivities0 = new startActivities0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("startActivitiesLandroid/content/ContextWrapper;VL",startActivities0));
	 startActivity0ApiHooker* startActivity0 = new startActivity0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("startActivityLandroid/content/ContextWrapper;VLL",startActivity0));
	 startRecording0ApiHooker* startRecording0 = new startRecording0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("startRecordingLandroid/media/AudioRecord;V",startRecording0));
	 startService0ApiHooker* startService0 = new startService0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("startServiceLandroid/content/ContextWrapper;LL",startService0));
	 store0ApiHooker* store0 = new store0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("storeLjava/security/KeyStore;VLC",store0));
	 StringBuffer0ApiHooker* StringBuffer0 = new StringBuffer0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("<init>Ljava/lang/StringBuffer;V",StringBuffer0));
	 takePicture0ApiHooker* takePicture0 = new takePicture0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("takePictureLandroid/hardware/Camera;VLLL",takePicture0));
	 //main函数调用不了
//	 toString0ApiHooker* toString0 = new toString0ApiHooker();
//	 mApiHookerHashMap.insert(make_pair("toStringLjava/lang/StringBuilder;L",toString0));
	 toURI0ApiHooker* toURI0 = new toURI0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("toURILjava/net/URL;L",toURI0));
	 traceInstructions0ApiHooker* traceInstructions0 = new traceInstructions0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("traceInstructionsLjava/lang/Runtime;VZ",traceInstructions0));
	 traceMethodCalls0ApiHooker* traceMethodCalls0 = new traceMethodCalls0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("traceMethodCallsLjava/lang/Runtime;VZ",traceMethodCalls0));
	 update0ApiHooker* update0 = new update0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("updateLandroid/content/ContentResolver;ILLLL",update0));
	 update1ApiHooker* update1 = new update1ApiHooker();
	 mApiHookerHashMap.insert(make_pair("updateLjavax/crypto/Cipher;BB",update1));
	 update2ApiHooker* update2 = new update2ApiHooker();
	 mApiHookerHashMap.insert(make_pair("updateLjava/security/MessageDigest;VB",update2));
	 update3ApiHooker* update3 = new update3ApiHooker();
	 mApiHookerHashMap.insert(make_pair("updateLandroid/database/sqlite/SQLiteDatabase;ILLLL",update3));
	 updateWithOnConflict0ApiHooker* updateWithOnConflict0 = new updateWithOnConflict0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("updateWithOnConflictLandroid/database/sqlite/SQLiteDatabase;ILLLLI",updateWithOnConflict0));
	 userActivity0ApiHooker* userActivity0 = new userActivity0ApiHooker();
	 mApiHookerHashMap.insert(make_pair("userActivityLandroid/os/PowerManager;VJZ",userActivity0));
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

