DDNS_BIN_DIR = $(PRJ_PATH)/DDNS/bin
DDNS_ETC_DIR = $(PRJ_PATH)/DDNS/etc
DDNS_KEY_DIR = $(PRJ_PATH)/DDNS/etc/key
DDNS_TOOL_DIR = $(PRJ_PATH)/DDNS/tools
BIND_DIR = $(PRJ_PATH)/DDNS/tools/bind-9.8.1-P1

export BIND_DIR
override CFLAGS = -Os
override LDFLAGS =
override LIBS =
override INCLUDEDIR =


all:
	$(Q)if [ ! -f $(DDNS_BIN_DIR)/nsupdate ];then \
	cd $(DDNS_TOOL_DIR); make ddns_program; fi

install:
	$(Q)echo "================  build DDNS ================" 
	$(Q)if [ ! -d  $(FS_PATH)/usr/local/etc/ddns ];then \
	mkdir $(FS_PATH)/usr/local/etc/ddns; fi
	$(Q)if [ ! -d  $(FS_PATH)/usr/local/etc/ddns/tmp ];then \
	mkdir $(FS_PATH)/usr/local/etc/ddns/tmp; fi	
	$(Q)cd $(DDNS_BIN_DIR); cp -f * $(FS_PATH)/sbin 
	$(Q)cd $(DDNS_ETC_DIR); cp -f $(PRJ_PATH)/DDNS/etc/services $(FS_PATH)/etc
	$(Q)if [ ! -f $(FS_PATH)/etc/resolv.conf ];then \
	ln -sf /nv/resolv.conf $(FS_PATH)/etc/resolv.conf; fi
	$(Q)ln -sf /nv/ddns/DDNS_CONFIG $(FS_PATH)/usr/local/etc/ddns/DDNS_CONFIG	
	$(Q)cp -f $(PRJ_PATH)/DDNS/etc/DDNS_CONFIG $(FS_PATH)/usr/local/etc/ddns/tmp
	$(Q)cd $(DDNS_KEY_DIR); cp -f * $(FS_PATH)/usr/local/etc/ddns
	$(Q)ln -sf /nv/ddns/ddns.key $(FS_PATH)/usr/local/etc/ddns/ddns.key
	$(Q)ln -sf /nv/ddns/ddns.private $(FS_PATH)/usr/local/etc/ddns/ddns.private
	$(Q)ln -sf /nv/bmc_hostname $(FS_PATH)/etc/bmc_hostname
	$(Q)cp -f $(PRJ_PATH)/DDNS/etc/key/ddns.key $(FS_PATH)/usr/local/etc/ddns/tmp
	$(Q)cp -f $(PRJ_PATH)/DDNS/etc/key/ddns.private $(FS_PATH)/usr/local/etc/ddns/tmp  
	$(Q)echo "================ build DDNS done ================"


CLEAN_FILES = $(BIND_DIR) bin/nsupdate
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk

SDK_FEATURE_NAME = DDNS
SDK_FILE_CP_LIST = ./bin/ddns_update.sh ./etc/DDNS_CONFIG ./etc/services ./etc/key/ddns.key \
./etc/key/ddns.private ./tools/Makefile ./tools/*.tar.gz ./Makefile

include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
