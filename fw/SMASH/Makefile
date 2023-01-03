-include $(PRJ_PATH)/.SDKPath
SMASHDIR = $(PRJ_PATH)/SMASH
CCLIBS = `pkg-config --libs libsfcc` `pkg-config --libs libcurl`
CCINCLUDE = `pkg-config --cflags libsfcc`  
SMASHDST = $(PRJ_PATH)/SMASH/SMASH
CXX = $(CROSS_COMPILE)gcc
HOST = $(subst -gcc,,$(notdir $(CROSS_COMPILE)gcc))
DBDIR = $(PRJ_PATH)/SMASH/dropbear
DROPBEAR_VERSION=2013.60
DBSRCDIR = $(PRJ_PATH)/SMASH/dropbear-$(DROPBEAR_VERSION)
SHELLDIR = $(SMASHDIR)/shell
TREE_UTIL_SRC_PATH = $(PRJ_PATH)/SMASH/tree-1.5.2.2-src/src/tree/1.5.2.2/tree-1.5.2.2-src
PKG_CONFIG_PATH = $(TC_LOCAL)/lib/pkgconfig
SMASH_VERSION = 1.05
DROPBEAR_ARM_CONF = -host=$(HOST) --prefix=$(DBDIR)  CPPFLAGS=-I$(PRJ_PATH)/SFCB/zlib-1.2.3/zlib/include \
					LDFLAGS="$(LDFLAGS) -L$(PRJ_PATH)/SFCB/zlib-1.2.3/zlib/lib -L$(PRJ_PATH)/lib" \
					--disable-syslog --disable-utmp --disable-utmpx --disable-lastlog CFLAGS=" -g $(CFLAGS) "
export PKG_CONFIG_PATH SMASHDST SMASH_VERSION


.PHONY: build_dropbear build_tree_utils

all:

install:
	$(Q)echo "************* SMASH ******************"
	$(Q)if [ ! -d $(DBDIR) ];then mkdir $(DBDIR); fi
	$(Q)if [ ! -d $(DBSRCDIR) ];then make build_dropbear ;fi
	$(Q)if [ ! -f $(DBDIR)/sbin/dropbear ];then make build_dropbear ;fi
	$(Q)echo "*************Install Shell******************"
	$(Q)if [ ! -d $(SMASHDST) ];then mkdir $(SMASHDST); fi
#	$(Q)if [ ! -d $(SMASHDST)/lib ];then mkdir $(SMASHDST)/lib;fi
	$(Q)cp -af $(SMASHDIR)/.smash_pkg/binlib/* $(SMASHDST)/ 
	cd $(SHELLDIR);make;
	$(Q)echo "*************Build Tree Utility******************"
	if [ ! -d ${TREE_UTIL_SRC_PATH} ];then make build_tree_utils;fi
	cp -af $(DBDIR) $(FS_PATH)/usr/local;
	chmod 777 -R $(SMASHDST);
	cp  $(SMASHDST)/lib/* $(FS_PATH)/lib;
	cp $(SMASHDIR)/smashd $(FS_PATH)/etc/init.d;
	chmod +x $(FS_PATH)/etc/init.d/smashd
	cp -af $(SMASHDST) $(FS_PATH);

build_dropbear:
	$(Q)tar jxf dropbear-$(DROPBEAR_VERSION).tar.bz2; 
	$(Q)cd $(DBSRCDIR); rm -f svr-authpasswd.c common-session.c;
	$(Q)cp -af $(SMASHDIR)/.smash_pkg/dbobj/*.o $(DBSRCDIR)/
	$(Q)cd $(DBSRCDIR); ./configure $(DROPBEAR_ARM_CONF); 
	$(Q)cd $(DBSRCDIR);make -j && make install;
	$(Q)cd $(DBDIR)/bin/;rm -rf dbclient  dropbearconvert; 
	$(Q)cd $(DBDIR);rm -rf share; 
	$(Q)$(STRIP) --strip-unneeded $(DBDIR)/sbin/dropbear; 
	$(Q)$(STRIP) --strip-unneeded $(DBDIR)/bin/dropbearkey; 

	
build_tree_utils:
	tar -zxf tree-1.5.2.2.tar.gz
	cd ${TREE_UTIL_SRC_PATH};make -j CC=${CC} prefix=${TREE_UTIL_SRC_PATH}/bin XOBJS=strverscmp.o
	cp -f ${TREE_UTIL_SRC_PATH}/tree $(SMASHDST)
	$(STRIP) --strip-unneeded $(SMASHDST)/tree;	

	
CLEAN_PATTERN = '*.d'
CLEAN_FILES = $(SMASHDST) $(DBSRCDIR) $(DBDIR)  tree-1.5.2.2-src dropbear_patch \
            shell/flex-2.5.35 shell/readline-5.2 shell/termcap-1.3.1 shell/shell shell/buil_shell SMASH/SMASH \
            $(call GEN_SEARCH_LIST,$(CLEAN_PATTERN),$(SMASHDIR),,) \
            $(call GEN_SEARCH_LIST,$(CLEAN_PATTERN),$(SHELLDIR),,)
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk
	

SDK_FEATURE_NAME = SMASH
SDK_FILE_CP_LIST = *.c *.tar.gz smashd  Makefile shell/*.tar.gz shell/Makefile

include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
