-include $(PRJ_PATH)/.config
-include $(PRJ_PATH)/.machine
SDKJavaAPSOL_DIR = $(SDKPATH)/JavaAP/SOL
all:

install:
	$(Q)$(PACK200) --repack SOL.jar;
	$(Q)$(JARSIGNER) -keystore $(KEYSTORE) -storepass $(STOREPASS) -keypass $(KEYPASS) -tsa $(TIME_SERVER)  SOL.jar $(PROVIDER)
	$(Q)$(PACK200) SOL.jar.pack.gz SOL.jar;
	$(Q)cp SOL.jar.pack.gz $(WEBFS_PATH)/SOL__V$(JAVA_SOL_VIEWER_FULL_VERSION).jar.pack.gz;
	$(Q)cp SOL.jar.pack.gz SOL__V$(JAVA_SOL_VIEWER_FULL_VERSION).jar.pack.gz;

CLEAN_FILES = SOL.jar.pack.gz
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk

extract:
