# 如何开启关闭jni层的时间采集


---
2015-10-15
桑耀辉

---
所谓关闭，就是既不采集时间戳，也不向java层发送时间Json
## 1.注释掉获取时间戳t1的代码
位置在DalvikMethodHooker.cpp 361 362行：
``` 
// 时间测试，记录处理Api的start时间，即t1
TimeUtils* timeUtils = TimeUtils::getInstance();
timeUtils->setT1StartTime();
```	
## 2.注释掉获取时间戳t2的代码
位置在InfoSender.cpp 91行
```
timeUtils->setT2EndTime();
```
## 3.使程序不发送时间测试的json。
InfoSender.cpp 94行改为 if(0)

---	
	
## PS
1.相应的可以把java层的com.lwl.utils.TimeTestUtils.java的CESHI_NUMBER设置很大，比如10000。间接关闭java层的时间采集和采集条数的限制。

2.修改CERSHI_NUMBER，有两处：
common.h 
com.lwl.utils.TimeTestUtils.java

3.在common.h中CESHI_NUMBER一定不能大于ARY_NUMBER，否则会溢出




