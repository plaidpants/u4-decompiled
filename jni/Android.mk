include $(CLEAR_VARS)

# override strip command to strip all symbols from output library; no need to ship with those..
# cmd-strip = $(TOOLCHAIN_PREFIX)strip $1 

LOCAL_ARM_MODE  := arm
LOCAL_PATH      := $(NDK_PROJECT_PATH)
LOCAL_MODULE    := TITLE
LOCAL_CFLAGS    := -fpack-struct=1 -w -xc -std=c89 -DDISABLE_WINDOWS -D__cdecl="" -Dcdecl="" -Dfar="" -Dhuge="" -fdeclspec -DSleep=usleep -Dstrnicmp=strncasecmp -DWIN32 -DSLEEPFACTOR=1000
LOCAL_SRC_FILES := forVS/u4title_main.c forVS/common.c SRC-TITLE/DATA.c SRC-TITLE/TITLE_0.c SRC-TITLE/TITLE_1.c SRC-TITLE/TITLE_X.c 
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)

# Don't strip debug builds
ifeq ($(APP_OPTIM),debug)
    cmd-strip := 
endif


