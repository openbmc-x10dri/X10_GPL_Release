-include $(PRJ_PATH)/.SDKPath
LIBS_SUITE_DIR = $(PRJ_PATH)/SFCC
HOST = $(subst -gcc,,$(notdir $(CROSS_COMPILE)gcc))
unexport CC LD AR CXX NM RANLIB OBJCOPY OBJDUMP \
STRIP CFLAGS LDFLAGS LIBS


PKG_CONFIG_PATH = $(TC_LOCAL)/lib/pkgconfig

CURL_VERIOSN  = 7.18.1
CURL_DIR      = $(LIBS_SUITE_DIR)/curl-$(CURL_VERIOSN)
SFCC_VERSION  = 2.1.0
SFCC_DIR      = $(LIBS_SUITE_DIR)/sblim-sfcc-$(SFCC_VERSION)
CURL_BUILD_DIR = $(LIBS_SUITE_DIR)/build_curl
SFCC_BUILD_DIR = $(LIBS_SUITE_DIR)/build_sfcc

CFG_CURL  = --prefix=$(CURL_BUILD_DIR) --exec-prefix=$(CURL_BUILD_DIR) CFLAGS=" -Os"

CFG_SFCC  = --prefix=$(SFCC_BUILD_DIR) --exec-prefix=$(SFCC_BUILD_DIR) CFLAGS=" -Os `pkg-config --libs libcurl`" 
CFG_HOST  = --host=$(HOST)

SFCC_CFG = --oldincludedir=$(TC_LOCAL)/include
SFCC_MFLAGS = libcimcClientXML_la_LIBADD=`pkg-config --libs libcurl` INCLUDES=`pkg-config --cflags libcurl`

CURL_CFG =\
--disable-largefile \
--disable-ftp \
--disable-file \
--disable-ldap \
--disable-ldaps \
--disable-dict \
--disable-telnet \
--disable-tftp \
--disable-manual \
--disable-ipv6 \
--disable-verbose \
--disable-sspi \
--disable-debug \
--disable-cookies \
--with-pic \
--without-libssh2 \
--without-gnutls \
--without-nss \
--without-ca-bundle \
--without-ca-path \
--without-libidn

export PKG_CONFIG_PATH LIBS_SUITE_DIR

.PHONY: CHECK_FOLDER build_curl build_sfcc CP_TASK
all: 

install: $(PKG_LIST) 
	make CHECK_FOLDER
	$(Q)echo "Build curl ........"
	if [ ! -d $(CURL_BUILD_DIR) ];then make build_curl;fi;
	$(Q)echo "Build sfcc ........"
	if [ ! -d $(SFCC_BUILD_DIR) ]; then make build_sfcc;fi;
	make CP_TASK

CHECK_FOLDER:
	if [ ! -d $(CURL_DIR) ];then tar jxf $(CURL_DIR).tar.bz2; fi
	if [ ! -d $(SFCC_DIR) ];then tar jxf $(SFCC_DIR).tar.bz2; \
	cd $(SFCC_DIR); patch -p1 < ../patch/struct_align.patch; cd $(LIBS_SUITE_DIR); fi

build_curl:	
	cd $(CURL_DIR); ./configure $(CFG_CURL) $(CFG_HOST) $(CURL_CFG);make -j; make install; make install-strip; 
	if [ ! -d $(PKG_CONFIG_PATH) ];then mkdir -p $(PKG_CONFIG_PATH); fi; 
	cp -af $(CURL_BUILD_DIR)/lib/pkgconfig/* $(PKG_CONFIG_PATH)/


build_sfcc:
	cd $(SFCC_DIR);./configure $(CFG_SFCC) $(CFG_HOST) $(SFCC_CFG); 
	cd $(SFCC_DIR);make -j $(SFCC_MFLAGS); 
	cd $(SFCC_DIR);make install; 
	cd $(SFCC_DIR);make install-strip; 

CP_TASK:
	cp -af $(CURL_BUILD_DIR)/lib/*.so* $(FS_PATH)/lib
	cp -af $(SFCC_BUILD_DIR)/lib/*.so* $(FS_PATH)/lib
	if [ ! -f $(PKG_CONFIG_PATH)/libsfcc.pc ];then \
	sed -e '1i prefix=$(SFCC_BUILD_DIR)' libsfcc.pc  > $(PKG_CONFIG_PATH)/libsfcc.pc;fi



CLEAN_FILES = $(CURL_DIR) $(SFCC_DIR) $(CURL_BUILD_DIR) $(SFCC_BUILD_DIR)
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk

SDK_FEATURE_NAME = SFCC
SDK_FILE_CP_LIST = *.tar.bz2 Makefile libsfcc.pc

include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
