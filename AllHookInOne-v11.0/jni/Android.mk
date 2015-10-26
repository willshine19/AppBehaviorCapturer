LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


LOCAL_MODULE    := onehook
#LOCAL_LDLIBS	:= -ldvm.4 -llog -landroid_runtime
#LOCAL_CFLAGS	:= -DDEBUG -O0
LOCAL_LDLIBS+= 
LOCAL_CFLAGS	:= -I./jni/AppBehaviorCapturer/ -I./jni/include/ -I./jni/dalvik/vm/ -I./jni/dalvik
LOCAL_LDFLAGS	:=	-L./jni/lib/  -L$(SYSROOT)/usr/lib -llog -ldvm -landroid_runtime 

#wildcard函数获取$(LOCAL_PATH)目录也就是jni目录下的所有后缀名为cpp的文件,并把结果放到变量MY_CPP_LIST里	
MY_CPP_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
#获取jni/AndroidSecuritySystem/ApiHook目录下的源文件,并追加到变量MY_CPP_LIST里
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/AppBehaviorCapturer/ApiHooker/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/AppBehaviorCapturer/ApiHooker/AndroidCommunication/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/AppBehaviorCapturer/ApiHooker/AndroidData/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/AppBehaviorCapturer/ApiHooker/AndroidSystem/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/AppBehaviorCapturer/ApiHooker/AndroidPeripheral/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/AppBehaviorCapturer/ApiInfo/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/AppBehaviorCapturer/InfoSender/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/AppBehaviorCapturer/System/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/AppBehaviorCapturer/Utils/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/AppBehaviorCapturer/Utils/json/*.cpp)

# 前面我们获取的文件都是以jni开头的,而真正编译所需要的文件都应该是直接从jni目录开始的,
# 所以我们使用模式替换把所有文件名前面的jni/去掉.
# $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)的语法含义,它的意思是对MY_CPP_LIST中每一项,应用冒号后面的规则,规则是什么呢?
# 规则是$(LOCAL_PATH)/%=%,意思是,查找所有$(LOCAL_PATH)/开头的项,并截取后面部分
LOCAL_SRC_FILES := $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)

LOCAL_SHARED_LIBRARIES += libcutils  
	
include $(BUILD_SHARED_LIBRARY)
