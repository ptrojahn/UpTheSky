LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Layers

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
	$(LOCAL_PATH)/Layers/include

# Add your application source files here...
LOCAL_SRC_FILES := $(subst $(LOCAL_PATH)/,,$(wildcard $(LOCAL_PATH)/Layers/*.cpp))

LOCAL_SHARED_LIBRARIES := SDL2

include $(BUILD_STATIC_LIBRARY)
