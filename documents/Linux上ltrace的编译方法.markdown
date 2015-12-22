# Linux上ltrace的编译方法

---
Author: 桑耀辉
Date: 2015-12-15

---

## 基本介绍
ltrace可以打印出程序运行过程中的库函数调用,
其原理是通过解析elf文件找到需要解析的符号及该符号所对应的地址.

在程序运行起来后, 首先使用ptrace, 将该符号对应的位置替换为软件中断.
这样在程序运行到该中断时会通知ltrace, ltrace从而能打印出当时所调用的函数.

## 环境
```
$ uname -a
Linux sang-Inspiron-N5110 3.13.0-32-generic #57-Ubuntu SMP Tue Jul 15 03:51:08 UTC 2014 x86_64 x86_64 x86_64 GNU/Linux
$ gcc --version
gcc (Ubuntu 4.8.2-19ubuntu1) 4.8.2
```

## 编译安装

### 1. 下载ltrace_0.7.3代码

```
$ wget http://ltrace.org/ltrace_0.7.3.orig.tar.bz2
```
用系统自带的解压工具解压缩，然后尝试编译
```
$ cd ltrace-0.7.3/
$ ./configure
```
可能报错configure: error: *** libelf.h or gelf.h not found on your system. 因为没有libelf库

### 2. 下载libelf

```
$ wget http://www.mr511.de/software/libelf-0.8.13.tar.gz
$ tar zxvf libelf-0.8.13.tar.gz
$ cd libelf-0.8.13/
$ ./configure --prefix=$HOME/libelf
$ make
$ make install
```

### 3. 编译ltrace

```
$ export C_INCLUDE_PATH=$C_INCLUDE_PATH:$HOME/libelf/include
$ export LIBRARY_PATH=$LIBRARY_PATH:$HOME/libelf/lib
$ ./configure
$ make
```
若编译时报如下错误，可以修改Makefile文件，将Makefile中的`-Werror`删掉，重新编译就可以了，可执行文件会出现在源码根目录

> value.c: In function 'value_init_deref':
value.c:287:15: error: typedef 'assert__long_enough_long' locally defined but not used [-Werror=unused-local-typedefs]
  typedef char assert__long_enough_long[-(sizeof(l) < sizeof(void *))];
  
## 参考资料
[Linux上编译ltrace](http://linxiaohui.github.io/linux/2014/08/06/ltrace-on-linux/)


