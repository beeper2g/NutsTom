LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

MY_FILES := hellocpp/main.cpp
MY_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/crypto/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/crypto/base64/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/crypto/md5/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/crypto/sha1/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/comm/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/data/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/game/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/menu/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/sdk/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/lua/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/lua/*.c)

MY_FILES := $(MY_FILES:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES := $(MY_FILES)

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/comm
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/crypto
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/crypto/base64
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/crypto/md5
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/crypto/sha1
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/data
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/game
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/sdk
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/lua
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/menu

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/extensions
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/extensions/GUI/CCControlExtension
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/extensions/CCBReader

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/cocos
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/cocos/editor-support

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES := cocosbuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
$(call import-module,extensions)
$(call import-module,editor-support/cocostudio)
$(call import-module,editor-support/cocosbuilder)
