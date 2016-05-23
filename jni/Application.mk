
# Uncomment this if you're using STL in your project
# See CPLUSPLUS-SUPPORT.html in the NDK documentation for more information
NDK_TOOLCHAIN_VERSION := clang
APP_PLATFORM := android-23
APP_STL := c++_shared
APP_CPPFLAGS += -std=c++11 -frtti
APP_ABI := armeabi-v7a
#x86 armeabi
