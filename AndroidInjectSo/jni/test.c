#include <jni.h>
// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>
#include <fcntl.h>
#include <android/log.h>
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,"injc",__VA_ARGS__)
jstring Java_com_auo_androidinjectso_MainActivity_stringFromJNI(JNIEnv* env, jobject thiz, jstring jstr) {

	const char *str = (*env) -> GetStringUTFChars(env, jstr, 0);

	int fdopen,fdread,fdwrite,fdclose;
	char buf[100]={0};
	char *string="DO NOT WRITE!!";
	//open
	fdopen = open("/data/data/com.auo.androidinjectso/files/s.txt",O_RDWR);
	if(fdopen==-1)
		LOGI("s.txt open FAILED!!! fdopen=%d",fdopen);		
	else
		LOGI("s.txt open SUCCESS!!!  fdopen=%d",fdopen);

	//read
	fdread=read(fdopen, buf, 30);
	if(fdread==-1)
		LOGI("s.txt read FAILED!!!   fdread=%d",fdread);		
	else
		LOGI("s.txt read SUCCESS!!!  fdread=%d, buf=%s",fdread,buf);

	//write
	fdwrite=write(fdopen,string,15);
	if(fdwrite==-1)
		LOGI("s.txt write FAILED!!!   fdwrite=%d",fdwrite);		
	else
		LOGI("s.txt write SUCCESS!!!  fdwrite=%d, buf=%s",fdwrite,string);

	//close
	fdclose=close(fdopen);
	if(fdclose==-1)
		LOGI("s.txt close FAILED!!!   fdclose=%d",fdclose);		
	else
		LOGI("s.txt close SUCCESS!!!  fdclose=%d",fdclose);


	if(strlen(str) == 10) {
		(*env)->ReleaseStringUTFChars(env, jstr, str);
		return (*env)->NewStringUTF(env, "Hook success");
	}
	else {
		(*env)->ReleaseStringUTFChars(env, jstr, str);
		return (*env)->NewStringUTF(env, "Hello  JNI");
	}
}
