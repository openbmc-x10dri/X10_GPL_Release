-include $(PRJ_PATH)/.config
-include $(PRJ_PATH)/.machine

#================= SDK param  ===================
SDK_FEATURE_NAME = PKConfig

PATTERN = '*.in'
SDK_FILE_CP_LIST = $(call GEN_SEARCH_LIST,$(PATTERN),Lx_Config/,,)


SDK_FILE_CP_LIST += ./Makefile \
EnvTool/*.rpm \
EnvTool/*.tar \
EnvTool/*.sh \
SDK_Diff/*.cpp \
SDK_Diff/*.awk \
SDK_Diff/*.sh \
Lx_Script/*.mk \
Lx_Script/*.sh \
Lx_Script/Buildcmd/*.sh \
Lx_Script/*.lib

#================= end of SDK param ===================
include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
