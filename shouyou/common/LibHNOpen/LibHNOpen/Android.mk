LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../LibHNUI)
$(call import-add-path,$(LOCAL_PATH)/../../LibHNNet)

LOCAL_MODULE := hn_open_static

LOCAL_MODULE_FILENAME := libHNOpen

LOCAL_SRC_FILES := ../UMeng/Cocos2dx/Android/CCUMSocialController.cpp \
                   ../UMeng/Cocos2dx/ShareButton/UMShareButton.cpp \
				   ../UMeng/Cocos2dx/Common/CCUMSocialSDK.cpp \
				   ../UMeng/UMengSocial.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.. \
                           $(LOCAL_PATH)/../../../../cocos2d \
                           $(LOCAL_PATH)/../../../../cocos2d/cocos \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \

LOCAL_EXPORT_LDLIBS := -llog \
                       -lz \
                       -landroid
                        
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += hn_ui_static
LOCAL_WHOLE_STATIC_LIBRARIES += hn_net_static

include $(BUILD_STATIC_LIBRARY)
                        
$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,editor-support/spine)
$(call import-module,extensions)
$(call import-module,LibHNUI)
$(call import-module,LibHNNet)