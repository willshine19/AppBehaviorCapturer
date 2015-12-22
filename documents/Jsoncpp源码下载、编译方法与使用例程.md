# Jsoncpp源码下载、编译方法与使用例程

标签（空格分隔）： 开发文档

---

Author：桑耀辉
Data：2015-12-8

---

## 1 下载安装python 
下载scon 
http://sourceforge.net/project/showfiles.php?group_id=30337&package_id=67375
下载jsoncpp-src-0.5.0 
http://jsoncpp.sourceforge.net/

## 2 安装scon 
在解压缩目录下 终端执行命令 
```
$ python setup.py install
```

## 3 编译json 　
解压json压缩包后在其解压后目录中运行 
```
$ scons platform=linux-gcc
```

编译出来的库文件在其libs/ linux-gcc-4.4.2目录下，有libjson_linux-gcc-4.4.2_libmt.so和libjson_linux-gcc-4.4.2_libmt.a。
头文件在解压目录下的include中。
我的jsoncpp安装在$HOME/usr/jsoncpp下。
```
$ mkdir ~/usr/jsoncpp
$ cp -r include ~/usr/jsoncpp
$ cp -r libs ~/usr/jsoncpp
```

## 4 Jsoncpp简单实例

1） 反序列化Json对象
　　比如一个Json对象的字符串序列如下,其中”array”:[...]表示Json对象中的数组：

{“key1”:”value1”,”array”:[{“key2”:”value2”},{“key2”:”value3”},{“key2”:”value4”}]}

　　那怎么分别取到key1和key2的值呢，代码如下所示:
```
#include <iostream>
#include <string>
#include "json/json.h"
 
int main(void)
{
     std::string strValue = "{\"key1\":\"value1\",\"array\":[{\"key2\":\"value2\"},{\"key2\":\"value3\"},{\"key2\":\"value4\"}]}";
 
     Json::Reader reader;
     Json::Value value;
 
     if (reader.parse(strValue, value))
     {
      std::string out = value["key1"].asString();
      std::cout << out << std::endl;
      const Json::Value arrayObj = value["array"];
      for (int i=0; i<arrayObj.size(); i++)
      {
           out = arrayObj[i]["key2"].asString();
           std::cout << out;
           if (i != arrayObj.size() - 1)
            std::cout << std::endl;
      }
     }
     return 0;
}
```

编译连接

```
$ g++ jscpp1.cpp -I$HOME/usr/jsoncpp/include/ ~/usr/jsoncpp/libs/linux-gcc-4.5.2/libjson_linux-gcc-4.5.2_libmt.a
$ ./a.out
value1
value2
value3
value4
```

2）序列化Json对象
　　先构建一个Json对象，此Json对象中含有数组，然后把Json对象序列化成字符串，代码如下：
```
#include <iostream>
#include <string>
#include "json/json.h"
 
int main(void)
{
     Json::Value root;
     Json::Value arrayObj;
     Json::Value item;
 
     for (int i = 0; i < 10; i ++)
     {
      item["key"] = i;
      arrayObj.append(item);
     }
 
     root["key1"] = "value1";
     root["key2"] = "value2";
     root["array"] = arrayObj;
     //root.toStyledString();
     std::string out = root.toStyledString();
     std::cout << out << std::endl;
     return 0;
}

编译连接
$ g++ jscpp2.cpp -I$HOME/usr/jsoncpp/include/ ~/usr/jsoncpp/libs/linux-gcc-4.5.2/libjson_linux-gcc-4.5.2_libmt.a
$ ./a.out
{
   "array" : [
      {
         "key" : 0
      },
      {
         "key" : 1
      },
      {
         "key" : 2
      },
      {
         "key" : 3
      },
      {
         "key" : 4
      },
      {
         "key" : 5
      },
      {
         "key" : 6
      },
      {
         "key" : 7
      },
      {
         "key" : 8
      },
      {
         "key" : 9
      }
   ],
   "key1" : "value1",
   "key2" : "value2"
}
```




