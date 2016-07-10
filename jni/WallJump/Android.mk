LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
	$(LOCAL_PATH)/../Layers/Layers/include

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	$(subst $(LOCAL_PATH)/,,$(wildcard $(LOCAL_PATH)/WallJump/*.cpp))

LOCAL_SHARED_LIBRARIES := SDL2
LOCAL_STATIC_LIBRARIES := Layers

LOCAL_LDLIBS := -lGLESv2 -llog -lOpenSLES -landroid

include $(BUILD_SHARED_LIBRARY)
