# 如何开启关闭向服务器端发送json


---
2015-10-15
桑耀辉

---
在SwipeListViewExampleActivity工程中，向服务器发送json的代码由com.syh.pubjson.JsonSender.java实现。
如何关闭？
在com.lwl.service.MultiThreadJsonReceiveThread.java中，注释掉126至130行
``` java
JsonSender sender = new JsonSender();
sender.login(); // login服务器
sender.subscribe(); //订阅
// 发送第一条JSON数据，指定内容
sender.pubFirstData(tm.getDeviceId());
```
注释掉163行
```
sender.publish(json);
```



