# NDK_PROJECT_PATH的问题

---
Author：桑耀辉
Date：2015年12月20日

---

## 问题
用ndk-build编译github上的ltrace for andoird的工程报错
> Android NDK: Could not find application project directory !    
Android NDK: Please define the NDK_PROJECT_PATH variable to point to it.    

## 分析
在用ndk-buld 编译c/c++工程的时候，会遇到上面提示的错误原因是你的当前目录不是一个名为“jni”的目录，所以`NDK_PROJECT_PATH`， `APP_BUILD_SCRIPT`， `NDK_APPLICATION_MK` 是一个空的值，ndk-build就没法只知道怎么编译而终止。 
## 解决
有两种办法：
a. 一个就是制定上面三个变量的值， 如：我要编译我当前目录的源文件， 当然包含Android.mk 和Application.mk 文件， 可以使用下面的命令编译（若没有Application.mk可以省掉第二部分）：
> ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_APPLICATION_MK=./Application.mk

b. 就是把这些文件放在一个jni目录下， 进入jni目录然后在编译。






