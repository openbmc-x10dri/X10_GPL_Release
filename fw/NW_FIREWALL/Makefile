FIREWALL_DIR	= $(PRJ_PATH)/NW_FIREWALL
#FIREWALL_ZIP   = $(wildcard $(FIREWALL_DIR)/*.tar.gz)
FIREWALL_VER    = iptables-1.4.21
FIREWALL_ZIP	= $(FIREWALL_DIR)/$(FIREWALL_VER).tar.bz2
FIREWALL_TMP	= $(FIREWALL_DIR)/tmp
FIREWALL_SRC	= $(FIREWALL_DIR)/$(FIREWALL_VER)

override CFLAGS = -Os 
override LDFLAGS =
override CPPFLAGS =
override LIBS =



all:
	
install:
	$(Q)if [ ! -d $(FIREWALL_TMP) ];then mkdir -p $(FIREWALL_TMP) ; fi
	$(Q)if [ ! -d $(FIREWALL_SRC) ];then tar -jxvf $(FIREWALL_ZIP) > /dev/null; fi
	$(Q)if [ ! -f $(FIREWALL_SRC)/config.h ];then \
	cd $(FIREWALL_SRC); ./configure --host=arm-linux --enable-static --prefix=$(FIREWALL_TMP) --exec-prefix=$(FIREWALL_TMP); \
    if [ -f config.h ];then make -j; make install; \
    cd $(FIREWALL_TMP); $(STRIP) ./lib/*.so; $(STRIP) ./sbin/xtables-multi; fi; fi
	$(Q)cd $(FIREWALL_TMP); cp -af ./bin/* $(FS_PATH)/bin/; cp -af ./sbin/* $(FS_PATH)/sbin/; cp -af ./lib/*so* $(FS_PATH)/lib/
	$(Q)cp -af ipfw  $(FS_PATH)/etc/init.d/;chmod +x $(FS_PATH)/etc/init.d/ipfw

CLEAN_FILES = $(FIREWALL_TMP) $(FIREWALL_SRC)
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk

SDK_FEATURE_NAME = NW_FIREWALL
SDK_FILE_CP_LIST = ./Makefile ./*.tar.bz2

include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
