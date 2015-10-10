------------------2015.5.27------------------------------
1 完成同一个ApiHooker的多线程安全问题；
2 修改框架，将ApiHooker的CollectedApiInfo成员删除，完成InfoSender与Queue的初始化代码
3 将整体代码融合，并跑通
------------------2015.5.21-------------------------------
根据讨论会建议修改代码，完成了
1 在DalvikMethodHooker.cpp中，完成了不同Api的通配，取消了使用swtich case进行分发的过程，这样即使今后增加新的Api，也不需要增添任何代码，使代码的可复用性提高
2 完成多态存在的问题，使得ApiHookerManager内部的成员变量mApiHookerHashMap使用过程中，使用对应子类的方法

------------------2015.5.14--------------------------------
1 将common.h，object.h放到AppBehaviorCapturer文件夹下,修改Androd.mk文件，使其包含的头文件目录包括AppBehaviorCapturer目录
2 修复部分命名：GetEnv修改为getEnv  g_JavaVM修改为mJavaVM
3 修复LOG调试信息的语法问题
4 修复XXXApiHooker的构造器，使各个APiHooker的初始化内容对外不可见
5 修复ApiHookerManager的成员函数的封闭性，将initHashMap,bindJavaMethodToNative改为private
6 关于DalvikMethodHooker.cpp内部的绑定过程，如何完成更好的通配，目前仍在完善，代码中未体现

--------------------2015.5.7----------------------------------------
根据讨论结果修改代码，完成ApiHookerManager的部分初始化工作
--------------------2015.5.22--------------------------------------
解决在hashmap中的ApiHooker的多态问题
--------------------2015.6.19------------------------------------
完成参数解析，并整合到工程中，包括：
1 FileOutputStream.write(int)方法解析int值
2 LocationManager.getLastKnownLocation(String)方法解析String值
3 ContentResolver.insert(Uri,ContentValue)方法解析Uri值
---------------------2015.6.26---------------------------------
1 ApiHooker的分类(AndroidCommunication,AndroidData,AndroidPeripheral,AndroidSystem)，并完成XXXApiHooker的代码编写
2 解决部分XXXApiHooker注入失败（注入过程中死掉），hook失败（注入过程正常，但在调用Api时程序异常退出），hook失效（注入过程完全成功，执行程序页不退出，但不输出对应的log信息）
～ps：<1>在这其中，修改了DalvikMethodHooker.cpp的dvmGetMethodParamTypes()源码，因为里面代码对数组的解析有些欠缺
<2>代码不乏对源码的阅读，所有的修改均是建立在源码理解的基础之上,不同的Android SDK版本都有可能会出现不一样的结果，以源码为准