-include $(PRJ_PATH)/.SDKPath
WSMAN_SUITE_DIR = $(PRJ_PATH)/OpenWSMAN
WSMAN_BUILD_DIR = $(WSMAN_SUITE_DIR)/build_wsman/openwsman
OPENWSMAN_VERSION = 2.1.0
OPENWSMAN_DIR = $(WSMAN_SUITE_DIR)/openwsman-$(OPENWSMAN_VERSION)

HOST = $(subst -gcc,,$(notdir $(CROSS_COMPILE)gcc))
unexport CC LD AR CXX NM RANLIB OBJCOPY OBJDUMP STRIP CFLAGS LDFLAGS LIBS

export PKG_CONFIG_PATH = $(TC_LOCAL)/lib/pkgconfig
CFG_HOST  = --host=$(HOST)

SUBSCR_DIR = /var/lib/openwsman/subscriptions
AUTH_DIR  =  /lib/openwsman/authenticators
PLUGIN_DIR = /lib/openwsman/plugins


WSMAN_CFG = --prefix=$(WSMAN_BUILD_DIR) --exec-prefix=$(WSMAN_BUILD_DIR) --disable-more-warnings
WSMAN_CFLAGS="-Wno-unused-but-set-variable   -Wno-enum-compare -Wno-strict-aliasing `pkg-config --cflags openssl`  -Os `pkg-config --cflags libcurl`  `pkg-config --cflags libsfcc` `pkg-config --libs libcurl` `pkg-config --libs libsfcc`\
			-DPACKAGE_SUBSCRIPTION_DIR=\\\"$(SUBSCR_DIR)\\\" -DPACKAGE_AUTH_DIR=\\\"$(AUTH_DIR)\\\" -DPACKAGE_PLUGIN_DIR=\\\"$(PLUGIN_DIR)\\\""
WSMAN_LDFLAGS = 

export PKG_CONFIG_PATH WSMAN_SUITE_DIR CFLAGS

.PHONY: CHECK_FOLDER BUILD_WSMAN HTPASSWD CP_TASK
all: 

install: CHECK_FOLDER
	$(Q)echo "Build openwsman ........"
	if [ ! -d $(WSMAN_BUILD_DIR) ]; then make BUILD_WSMAN;fi
	$(Q)echo "Build htpasswd ........"
	if [ ! -f $(WSMAN_SUITE_DIR)/htpasswd ];then make HTPASSWD;fi;
	make CP_TASK;

CHECK_FOLDER:
	if [ ! -d $(OPENWSMAN_DIR) ];then \
	cd $(WSMAN_SUITE_DIR); tar zxf openwsman-$(OPENWSMAN_VERSION).tar.gz; fi
	
BUILD_WSMAN:
	cd $(OPENWSMAN_DIR);CFLAGS=$(WSMAN_CFLAGS) ./configure $(WSMAN_CFG) $(CFG_HOST) CC=$(CROSS_COMPILE)gcc RANLIB=$(CROSS_COMPILE)ranlib CXX=$(CROSS_COMPILE)g++ STRIP=$(CROSS_COMPILE)strip; 
	cd $(OPENWSMAN_DIR); make -j 
	cd $(OPENWSMAN_DIR);make install; make install-strip; 

HTPASSWD:
	cd $(WSMAN_SUITE_DIR); tar zxvf apache.tar.gz; 
	cd $(WSMAN_SUITE_DIR)/apache/apache_1.3.42; \
	CC=$(CROSS_COMPILE)gcc CFLAGS=-Os bash ./configure --without-execstrip --enable-module=so && \
	 make -j && cp -f $(WSMAN_SUITE_DIR)/apache/apache_1.3.42/src/support/htpasswd $(WSMAN_SUITE_DIR); \
	$(STRIP) $(WSMAN_SUITE_DIR)/htpasswd; chmod 777 $(WSMAN_SUITE_DIR)/htpasswd; rm -rf $(WSMAN_SUITE_DIR)/apache; 

CP_TASK:
	chmod 777 -R $(WSMAN_BUILD_DIR)
	find $(WSMAN_BUILD_DIR)/lib/ -name "*.la" | xargs rm -rf
	find $(WSMAN_BUILD_DIR)/lib/ -name "*.a"  | xargs rm -rf
	rm -rf $(WSMAN_BUILD_DIR)/include
	cp -af $(WSMAN_BUILD_DIR)/* $(FS_PATH)/
	if [ -d $(FS_PATH)/etc/openwsman/ ] ;then mkdir -p $(FS_PATH)/etc/openwsman/;fi; \
	rm -rf $(WSMAN_SUITE_DIR)/conf/digest_auth.passwd
	cp -rf $(WSMAN_SUITE_DIR)/conf/* $(FS_PATH)/etc/openwsman/
	cp -rf $(WSMAN_SUITE_DIR)/conf/openwsmand $(FS_PATH)/etc/init.d/ && chmod a+x $(FS_PATH)/etc/init.d/openwsmand
	cp -f $(WSMAN_SUITE_DIR)/htpasswd $(FS_PATH)/bin/
	cd $(FS_PATH)/etc/openwsman/; \
	ln -s /nv/wsman/simple_auth.passwd simple_auth.passwd
CLEAN_FILES = $(WSMAN_SUITE_DIR)/htpasswd $(WSMAN_SUITE_DIR)/build_wsman/ $(OPENWSMAN_DIR)
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk

SDK_FEATURE_NAME = OpenWSMAN
SDK_FILE_CP_LIST = *.tar.gz  wsman_account_handler.c apache.tar.gz  Makefile inc/*.h conf/*

include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
