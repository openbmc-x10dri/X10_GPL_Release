-include $(PRJ_PATH)/.config
-include $(PRJ_PATH)/.machine
include $(PRJ_PATH)/PKConfig/Lx_Script/Makefile.lib
LIB_PATH               = lib
LINUX_LIB_PATH         = $(LIB_PATH)
WINDOWS_LIB_PATH       = $(LIB_PATH)
MAC_LIB_PATH           = $(LIB_PATH)
IKVM_JAR_NAME          = iKVM__V$(JAVA_KVM_VIEWER_FULL_VERSION).jar
LIB_LINUX_X86_NAME     = liblinux_x86__V$(JAVA_KVM_LIB_VERSION).jar
LIB_LINUX_X86_X64_NAME = liblinux_x86_64__V$(JAVA_KVM_LIB_VERSION).jar
LIB_WIN_X86_NAME       = libwin_x86__V$(JAVA_KVM_LIB_VERSION).jar
LIB_WIN_X86_X64_NAME   = libwin_x86_64__V$(JAVA_KVM_LIB_VERSION).jar
LIB_MAC_X86_X64_NAME   = libmac_x86_64__V$(JAVA_KVM_LIB_VERSION).jar

override CFLAGS = 
override LDFLAGS = 
override LIBS =


all:

install: JAR
	$(Q)cp $(IKVM_JAR_NAME).pack.gz $(WEBFS_PATH);
	$(Q)cp $(LIB_LINUX_X86_NAME).pack.gz $(WEBFS_PATH);
	$(Q)cp $(LIB_LINUX_X86_X64_NAME).pack.gz $(WEBFS_PATH);
	$(Q)cp $(LIB_WIN_X86_NAME).pack.gz $(WEBFS_PATH);
	$(Q)cp $(LIB_WIN_X86_X64_NAME).pack.gz $(WEBFS_PATH);
	$(Q)cp $(LIB_MAC_X86_X64_NAME).pack.gz $(WEBFS_PATH);

JAR:
	$(Q)$(ECHO_CMD) "Sign iKVM.jar";
	$(Q)$(PACK200) --repack $(IKVM_JAR_NAME);
	$(Q)$(JARSIGNER) -keystore $(KEYSTORE) -storepass $(STOREPASS) -keypass $(KEYPASS) -tsa $(TIME_SERVER) $(IKVM_JAR_NAME) $(PROVIDER)  
	$(Q)$(PACK200) $(IKVM_JAR_NAME).pack.gz $(IKVM_JAR_NAME);
	$(Q)$(ECHO_CMD) "Generate liblinux_x86.jar"
	$(Q)$(JAR) -cfm $(LIB_LINUX_X86_NAME) $(MANIFEST) -C $(LINUX_LIB_PATH) libSharedLibrary32.so -C $(LINUX_LIB_PATH) libiKVM32.so
	$(Q)$(PACK200) --repack $(LIB_LINUX_X86_NAME);
	$(Q)$(JARSIGNER) -keystore $(KEYSTORE) -storepass $(STOREPASS) -keypass $(KEYPASS) -tsa $(TIME_SERVER) $(LIB_LINUX_X86_NAME) $(PROVIDER)  
	$(Q)$(PACK200) $(LIB_LINUX_X86_NAME).pack.gz $(LIB_LINUX_X86_NAME);
	$(Q)$(ECHO_CMD) "Generate liblinux_x86_64.jar"
	$(Q)$(JAR) -cfm $(LIB_LINUX_X86_X64_NAME) $(MANIFEST) -C $(LINUX_LIB_PATH) libSharedLibrary64.so -C $(LINUX_LIB_PATH) libiKVM64.so
	$(Q)$(PACK200) --repack $(LIB_LINUX_X86_X64_NAME);
	$(Q)$(JARSIGNER) -keystore $(KEYSTORE) -storepass $(STOREPASS) -keypass $(KEYPASS) -tsa $(TIME_SERVER) $(LIB_LINUX_X86_X64_NAME) $(PROVIDER)  
	$(Q)$(PACK200) $(LIB_LINUX_X86_X64_NAME).pack.gz $(LIB_LINUX_X86_X64_NAME);
	$(Q)$(ECHO_CMD) "Generate libwin_x86.jar"
	$(Q)$(JAR) -cfm $(LIB_WIN_X86_NAME) $(MANIFEST) -C $(WINDOWS_LIB_PATH) SharedLibrary32.dll -C $(WINDOWS_LIB_PATH) iKVM32.dll
	$(Q)$(PACK200) --repack $(LIB_WIN_X86_NAME);
	$(Q)$(JARSIGNER) -keystore $(KEYSTORE) -storepass $(STOREPASS) -keypass $(KEYPASS) -tsa $(TIME_SERVER) $(LIB_WIN_X86_NAME) $(PROVIDER)  
	$(Q)$(PACK200) $(LIB_WIN_X86_NAME).pack.gz $(LIB_WIN_X86_NAME);
	$(Q)$(ECHO_CMD) "Generate libwin_x86_64.jar"
	$(Q)$(JAR) -cfm $(LIB_WIN_X86_X64_NAME) $(MANIFEST) -C $(WINDOWS_LIB_PATH) SharedLibrary64.dll -C $(WINDOWS_LIB_PATH) iKVM64.dll
	$(Q)$(PACK200) --repack $(LIB_WIN_X86_X64_NAME);
	$(Q)$(JARSIGNER) -keystore $(KEYSTORE) -storepass $(STOREPASS) -keypass $(KEYPASS) -tsa $(TIME_SERVER) $(LIB_WIN_X86_X64_NAME) $(PROVIDER)  
	$(Q)$(PACK200) $(LIB_WIN_X86_X64_NAME).pack.gz $(LIB_WIN_X86_X64_NAME);
	$(Q)$(ECHO_CMD) "Generate libmac_x86_64.jar"
	$(Q)$(JAR) -cfm $(LIB_MAC_X86_X64_NAME) $(MANIFEST) -C $(MAC_LIB_PATH) libSharedLibrary64.jnilib -C $(MAC_LIB_PATH) libiKVM64.jnilib
	$(Q)$(PACK200) --repack $(LIB_MAC_X86_X64_NAME);
	$(Q)$(JARSIGNER) -keystore $(KEYSTORE) -storepass $(STOREPASS) -keypass $(KEYPASS) -tsa $(TIME_SERVER) $(LIB_MAC_X86_X64_NAME) $(PROVIDER)  
	$(Q)$(PACK200) $(LIB_MAC_X86_X64_NAME).pack.gz $(LIB_MAC_X86_X64_NAME);


CLEAN_FILES = $(IKVM_JAR_NAME).pack.gz \
    $(LIB_LINUX_X86_NAME) $(LIB_LINUX_X86_NAME).pack.gz \
    $(LIB_LINUX_X86_X64_NAME) $(LIB_LINUX_X86_X64_NAME).pack.gz \
    $(LIB_WIN_X86_NAME) $(LIB_WIN_X86_NAME).pack.gz \
    $(LIB_WIN_X86_X64_NAME) $(LIB_WIN_X86_X64_NAME).pack.gz \
    $(LIB_MAC_X86_X64_NAME) $(LIB_MAC_X86_X64_NAME).pack.gz
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk

