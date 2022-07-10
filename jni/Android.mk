include $(CLEAR_VARS)

# override strip command to strip all symbols from output library; no need to ship with those..
# cmd-strip = $(TOOLCHAIN_PREFIX)strip $1 

LOCAL_ARM_MODE  := arm
LOCAL_PATH      := $(NDK_PROJECT_PATH)
LOCAL_MODULE    := TITLE
LOCAL_CFLAGS    := -w -xc -std=c89 -DDISABLE_WINDOWS -Dcdecl="" -Dfar="" -Dhuge="" -fdeclspec -DSleep=sleep
LOCAL_SRC_FILES := forVS/u4title_main.c forVS/common.c SRC-TITLE/DATA.c SRC-TITLE/TITLE_0.c SRC-TITLE/TITLE_1.c SRC-TITLE/TITLE_X.c 
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)
