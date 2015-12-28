# 交叉编译strace方法

---
Author: 桑耀辉
Date: 2015年12月28日

---
## 背景

在ubuntu环境下交叉编译出Android平台可以运行的strace可执行文件。本文所使用的strace源码版本为4.11。


## 1 下载交叉编译器

```
$ sudo apt-get install gcc-arm-linux-gnueabi
```

## 2 下载strace源代码

strace 4.11 源代码 [下载地址](http://sourceforge.net/projects/strace/files/latest/download)

## 3 解压缩

```
$ tar xf strace-4.11.tar.xz
$ cd strace-4.11
```

## 4 设置环境变量并编译

```
$ export CC=/usr/bin/arm-linux-gnueabi-gcc
$ export STRIP=arm-linux-gnueabi-strip
$ export CFLAGS="-march=armv7-a -O2 -static"
$ ./configure --host=arm-linux
$ make
$ $STRIP strace
```
用file命令可以查看生成可执行文件的格式

```
$ file strace
strace: ELF 32-bit LSB  executable, ARM, EABI5 version 1 (SYSV), statically linked, for GNU/Linux 2.6.32, BuildID[sha1]=a3b4a398e9293d25d63fdb4fceb881b5f6dd9c75, stripped
```

## 5 push到测试机

将编译生成的可执行文件push到测试
```
$ adb push strace /data/inj-allhookinone
```

## 6 测试strace

```
$ adb shell
$ cd /data/inj-allhookinone
$ ./strace -V
```
若可以显示版本号说明这个可执行文件可以执行。

## 参考资料

[STrace 4.8 - Ultimate debugging utility now ported to Android !](http://forum.xda-developers.com/showthread.php?t=2516002&page=3)
[How to compile strace for use on an Android phone (running an ARM CPU)](http://muzso.hu/2012/04/21/how-to-compile-strace-for-use-on-an-android-phone-running-an-arm-cpu)
[源码下载地址1](http://sourceforge.net/projects/strace/)
[源码下载地址2](https://android.googlesource.com/platform/external/strace.git/)

