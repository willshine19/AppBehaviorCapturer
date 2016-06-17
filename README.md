## 注入控制app

---
该工程是一个eclipse的android app工程。用于控制对指定app的注入。

该app的正常工作依赖于两个子模块：进程注入程序和so库。

进程注入程序的源代码在android_injection / c_layer_injector中，需要用ndk编译成可执行程序，然后adb push到测试机的指定位置。注入控制app会通过这个路径启动进程注入程序。

so库的源代码在 android_injection / dalvik_jni_hooker_lib中，需要用ndk编译成一个so库，然后adb psuh到测试机的指定位置。