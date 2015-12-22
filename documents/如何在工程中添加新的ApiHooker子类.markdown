# 如何在工程中添加新的ApiHooker子类


---
2015-10-13
作者：桑耀辉

---
## 步骤
### 1.创建类
在jni/AppBehaviorCapturer/ApiHooker目录下相应的位置创建类（包括.cpp和.h）,继承ApiHooker类或者VoidApiHooker类。
在.h文件中include父类头文件，并声明将要重写的方法。例如：
```
#include "../VoidApiHooker.h"
class OnCreateActivityApiHooker:public VoidApiHooker{
public:
	OnCreateActivityApiHooker();
	virtual ~OnCreateActivityApiHooker();
};
```
在.cpp文件中重写构造方法，例如：
```
OnCreateActivityApiHooker::OnCreateActivityApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"onCreate","(Landroid/os/Bundle;)V", false, NULL, NULL, NULL));
}
```
### 2.实例化并插入hashmap
在jni/AppBehaviorCapturer/System/ApiHookerManager.cpp中的initHashMap方法中添加类的实例化代码和插入哈希表的代码。例如：
```
OnCreateActivityApiHooker* onCreate = new OnCreateActivityApiHooker();
mApiHookerHashMap.insert(make_pair("onCreate", onCreate));
```
### 3.include 头文件
在jni/AppBehaviorCapturer/System/ApiHookerManager.h中include新类的.h文件。例如：
```
#include "../ApiHooker/AndroidSystem/OnCreateActivityApiHooker.h"
```



