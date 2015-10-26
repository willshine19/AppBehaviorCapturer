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

