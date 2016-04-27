APP_STL := gnustl_static
#在工程中使用unordered_map类实现哈希表，必须支持c++11的编译器编译才不会报错。
NDK_TOOLCHAIN_VERSION = 4.9 #不同版本的ndk导致这个工具连版本号不同，如果你无法ndk-build，请尝试将4.9改为4.8
APP_CPPFLAGS := -frtti -std=c++11
APP_CPPFLAGS += -fexceptions
