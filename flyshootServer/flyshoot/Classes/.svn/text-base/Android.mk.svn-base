LOCAL_PATH = $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE = game_logic_static

LOCAL_MODULE_FILENAME = libgame_logic

LOCAL_SRC_FILES = *.cpp \ 
				  *.hpp \
				  *.h
                   
LOCAL_EXPORT_C_INCLUDES = $(LOCAL_PATH)

LOCAL_STATIC_LIBRARIES = png_static_prebuilt
LOCAL_STATIC_LIBRARIES += xml2_static_prebuilt
LOCAL_STATIC_LIBRARIES += jpeg_static_prebuilt
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
                
LOCAL_SHARED_LIBRARIES = cocosdenshion_shared
            
include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dxplatformthird_partyandroidmoduleslibpng)
$(call import-module,cocos2dxplatformthird_partyandroidmoduleslibxml2)
$(call import-module,cocos2dxplatformthird_partyandroidmoduleslibjpeg)
