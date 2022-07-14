include $(CLEAR_VARS)

# override strip command to strip all symbols from output library; no need to ship with those..
# cmd-strip = $(TOOLCHAIN_PREFIX)strip $1 

LOCAL_ARM_MODE  := arm
LOCAL_PATH      := $(NDK_PROJECT_PATH)
LOCAL_MODULE    := AVATAR
LOCAL_CFLAGS    := -w -xc -std=c89 -DDISABLE_WINDOWS -D__cdecl="" -Dcdecl="" -Dfar="" -Dhuge="" -fdeclspec -DSleep=usleep -Dstrnicmp=strncmp
LOCAL_SRC_FILES := forVS/u4_forWin.c forVS/common.c forVS/lzw.c SRC/U4_3D.c SRC/U4_AI.c SRC/U4_ANIM.c SRC/U4_COMBA.c SRC/U4_COMBB.c SRC/U4_COMBC.c SRC/U4_CSTES.c SRC/U4_DNG.c SRC/U4_END.c SRC/U4_EVT.c SRC/U4_EXPLO.c SRC/U4_FILE.c  SRC/U4_GET.c SRC/U4_HOLE.c SRC/U4_INIT.c SRC/U4_LB.c SRC/U4_LOCAT.c SRC/U4_MAIN.c SRC/U4_MAIN2.c SRC/U4_MAP.c SRC/U4_MIX.c SRC/U4_NPC.c SRC/U4_PEER.c SRC/U4_Q_N_V.c SRC/U4_SHOPS.c SRC/U4_SHRIN.c SRC/U4_SPELL.c SRC/U4_SRCH.c SRC/U4_SRCH2.c SRC/U4_TALK.c SRC/U4_USE.c SRC/U4_UTIL.c forVS/U4_VAR.c SRC/U4_Z.c
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)

# Don't strip debug builds
ifeq ($(APP_OPTIM),debug)
    cmd-strip := 
endif