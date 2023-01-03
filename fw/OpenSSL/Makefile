-include $(PRJ_PATH)/.SDKPath
SSL_SRCDIR = $(PRJ_PATH)/OpenSSL
SSL_ZIP    = $(wildcard $(SSL_SRCDIR)/*.tar.gz)
SSL_PKG    = openssl-1.0.1p
SSL_FOLDER = $(SSL_SRCDIR)/$(SSL_PKG)
SSL_CFG    = no-asm no-camellia no-gmp no-krb5 no-mdc2 no-rc5 no-rfc3779 no-seed \
shared no-zlib --prefix=$$PWD/local/ --openssldir=$$PWD/local/ssl
SSL_MFG    = AR="$(CROSS_COMPILE)ar r"

DTKSSL_DIR = $(DTKPATH)/OpenSSL

override CFLAGS = 
override LDFLAGS =
Q=

all:
	$(Q)echo "******************** make OpenSSL ********************"
	$(Q)set -e;cd $(SSL_SRCDIR); \
	if [ ! -d $(SSL_PKG) ];then tar zxf $(SSL_ZIP); \
	cd $(SSL_FOLDER);./config $(SSL_CFG); make $(SSL_MFG);\
	make install; fi
	$(Q)set -e;cd $(SSL_FOLDER);$(STRIP) local/lib/*.so.*; $(STRIP) apps/openssl;\
	cp libcrypto.so libssl.so $(PRJ_PATH)/lib; \
	if [ ! -d $(TC_LOCAL)/lib/pkgconfig ];then mkdir $(TC_LOCAL)/lib/pkgconfig;fi;\
	cp -f local/lib/pkgconfig/* $(TC_LOCAL)/lib/pkgconfig/ 
	$(Q)cp $(SSL_FOLDER)/local/lib/libcrypto.so $(PRJ_PATH)/lib/
	$(Q)cp $(SSL_FOLDER)/local/lib/libssl.so $(PRJ_PATH)/lib/
	$(Q)cp $(SSL_FOLDER)/apps/openssl $(PRJ_PATH)/bin
	$(Q)if [ ! -s $(SSL_SRCDIR)/openssl ];then ln -s $(SSL_FOLDER) openssl;fi
	$(Q)cd $(PRJ_PATH)/lib;if [ ! -f libcrypto.so.1.0.0 ];then ln -s libcrypto.so libcrypto.so.1.0.0;\
	ln -s libssl.so libssl.so.1.0.0;fi

CLEAN_FILES = $(SSL_FOLDER) openssl
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk
#================= SDK param  ===================
SDK_FEATURE_NAME = OpenSSL
SDK_FILE_CP_LIST = Makefile $(SSL_ZIP) 
#================= end of SDK param ===================
include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
