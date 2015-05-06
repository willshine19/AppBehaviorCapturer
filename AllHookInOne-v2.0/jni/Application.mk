APP_STL := gnustl_static
#在工程中使用unordered_map类实现哈希表，必须支持c++11的编译器编译才不会报错。
NDK_TOOLCHAIN_VERSION = 4.8
APP_CPPFLAGS := -frtti -std=c++11