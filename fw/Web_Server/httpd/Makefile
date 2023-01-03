-include $(PRJ_PATH)/.SDKPath
HTTPD_SRCDIR = $(PRJ_PATH)/Web_Server/httpd
LIGHTTPD_VER = 1.4.32
LIBPCRE_VER  = 8.33
HTTPD_ZIP    = $(HTTPD_SRCDIR)/lighttpd-$(LIGHTTPD_VER).tar.gz
LIBPCRE_TAR	 = $(HTTPD_SRCDIR)/pcre-$(LIBPCRE_VER).tar.gz
LIBPCRE_SRCDIR	 = $(PRJ_PATH)/Web_Server/httpd/pcre-$(LIBPCRE_VER)
LIBPCRE_DESTDIR	 = $(HTTPD_SRCDIR)/build_libpcre

ARM_HOST_GCC   = --host=$(subst -gcc,,$(notdir $(CROSS_COMPILE)gcc))
LIGHTTPD_PREFIX = --prefix=$(HTTPD_SRCDIR)/lighttpd/local \
				  --exec-prefix=$(HTTPD_SRCDIR)/lighttpd/local \
				  CFLAGS=" -I$(LIBPCRE_DESTDIR)/include" \
				  LDFLAGS=" -L$(LIBPCRE_DESTDIR)/lib -lpcre"

LIGHTTPD_CONF   = --with-openssl=$(PRJ_PATH)/OpenSSL/openssl/local/ssl \
--without-zlib --without-bzip2 --with-pcre \
--with-openssl-includes=$(PRJ_PATH)/OpenSSL/openssl/local/include \
--with-openssl-libs=$(PRJ_PATH)/OpenSSL/openssl/local/lib

PCRE_PREFIX = --prefix=$(LIBPCRE_DESTDIR)
DTKHTTPD_DIR = $(DTKPATH)/Web_Server/httpd
override CFLAGS = 
override LDFLAGS =
override LIBS =

START_DATE=$(shell date +"%g%m%d")
END_DATE=$(shell date +"%g%m%d" --date="+3 year")

all:

install:
#copy httpd
	if [ ! -d $(LIBPCRE_DESTDIR) ];then cd $(HTTPD_SRCDIR); tar zxvf $(LIBPCRE_TAR); \
	set -e; \
	cd $(LIBPCRE_SRCDIR); \
	./configure $(ARM_HOST_GCC) $(PCRE_PREFIX); \
	make  -j;make install;make install-strip;fi; 
	$(Q)echo "******************** make httpd ********************"
	$(Q)if [ ! -d $(HTTPD_SRCDIR)/lighttpd ];then cd $(HTTPD_SRCDIR); tar zxvf $(HTTPD_ZIP); fi
	set -e; \
	if [ ! -d $(HTTPD_SRCDIR)/lighttpd/local ]; then \
	cd $(HTTPD_SRCDIR)/lighttpd; \
	./configure $(ARM_HOST_GCC) $(LIGHTTPD_PREFIX) $(LIGHTTPD_CONF) ; \
	make; make install; make install-strip; fi
	cp $(LIBPCRE_DESTDIR)/lib/libpcre.so*	$(PRJ_PATH)/lib; 
	$(Q)if [ ! -d  $(FS_PATH)/usr/local/httpd ];then \
	mkdir $(FS_PATH)/usr/local/httpd; fi
	$(Q)cd $(HTTPD_SRCDIR); \
	cp -f server.pem $(FS_PATH)/usr/local/httpd/; \
	cp -f *.conf $(FS_PATH)/usr/local/httpd/; \
	cp -rf lighttpd/local/*  $(FS_PATH)/usr/local/httpd/; \
	cp -fd httpd $(FS_PATH)/etc/init.d; \
	sed -i 's/\(START_DATE=\)/\1${START_DATE}000000Z/' $(FS_PATH)/etc/ssl/CA.sh ;\
	sed -i 's/\(END_DATE=\)/\1${END_DATE}000000Z/' $(FS_PATH)/etc/ssl/CA.sh;\
	rm -rf $(FS_PATH)/usr/local/httpd/share/man;
	
CLEAN_FILES =  $(HTTPD_SRCDIR)/lighttpd local $(HTTPD_SRCDIR)/pcre-8.33 $(HTTPD_SRCDIR)/build_libpcre
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk

extract:
