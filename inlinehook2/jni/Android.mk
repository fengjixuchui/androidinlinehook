LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm
LOCAL_MODULE    := inline_hook
LOCAL_SRC_FILES := inline_hook.c foo.c

LOCAL_STATIC_LIBRARIES += libc
LOCAL_LDFLAGS := -static

include $(BUILD_EXECUTABLE)