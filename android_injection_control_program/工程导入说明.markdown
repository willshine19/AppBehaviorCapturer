# 工程导入说明

Author：刘文龙

---

## 一、文件介绍

本工程共有两个部分，分别为`main`和`SwipeListViewExampleActivity`。
**main工程**为基础工程，主要提供给android程序一个可以左右滑动的列表，其内部并没有具体的数据和按键。
**SwipeListViewExampleActivity工程**为具体实现，它引入了main工程，并在此基础上添加了数据与所需的按钮。

## 二、具体使用

使用时需引入两个工程，之后在main工程的properties中的android设置is library。

![tu1](http://img.blog.csdn.net/20151221155221481?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

之后在SwipeListViewExampleActivity的相同界面上添加

![tu2](http://img.blog.csdn.net/20151221155255954?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

之后便可以运行SwipeListViewExampleActivity。
对于修改来说，界面设计几乎不需要更改基础的main文件，只要在SwipeListViewExampleActivity中修改即可。

---

### 可能出现的问题：

``` 
caused by java.lang.classnotfoundexception:didn't find class *** on path:/data/app/***
```

### 解决

可能是android-support-v4.jar版本问题，将sdk中的android-support-v4.jar考到main工程的libs下。




