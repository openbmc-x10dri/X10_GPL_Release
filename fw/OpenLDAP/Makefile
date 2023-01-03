-include $(PRJ_PATH)/.SDKPath
HOST = $(subst -gcc,,$(notdir $(CROSS_COMPILE)gcc))

ifeq ($(MYMCU),YARKON)
GNU_SRC_ARG=-D_GNU_SOURCE
else
GNU_SRC_ARG=
endif
	
LDAP_SRCDIR = $(PRJ_PATH)/OpenLDAP
LDAP_CFG    =  --with-tls=openssl --without-kerberos --disable-debug --without-cyrus-sasl \
--without-threads --disable-slapd --disable-slurpd --disable-shared \
-host=${HOST} \
CFLAGS="-I$(PRJ_PATH)/OpenSSL/openssl/local/include -fPIC" \
CPPFLAGS="-I$(PRJ_PATH)/OpenSSL/openssl/local/include $(GNU_SRC_ARG)" \
LDFLAGS="-L$(PRJ_PATH)/OpenSSL/openssl/local/lib -lcrypto -lssl -lpthread"
LDAP_DIR=openldap-2.4.40
LDAP_ZIP=openldap-2.4.40.tgz

DTKLDAP_DIR = $(DTKPATH)/OpenLDAP

override CFLAGS = 
override LDFLAGS = 
override LIBS =
all:
	$(Q)echo "******************** make OpenLDAP ********************"
	$(Q)cd $(LDAP_SRCDIR); \
	if [ ! -d $(LDAP_DIR) ];then tar zxf $(LDAP_ZIP);fi
	$(Q)cd $(LDAP_SRCDIR)/$(LDAP_DIR);if [ ! -f $(LDAP_SRCDIR)/$(LDAP_DIR)/libraries/libldap/.libs/libldap.a ];then \
	./configure $(LDAP_CFG); patch -p0 < ../patch/patch_memcmp.patch;make depend; make -j;fi

install:
	$(Q)echo "************** copy OpenLDAP config to FS*************"
	$(Q)if [ ! -d  $(FS_PATH)/usr/local/etc ];then mkdir $(FS_PATH)/usr/local/etc; fi
	$(Q)cd $(LDAP_SRCDIR); cp -r openldap-config $(FS_PATH)/usr/local/etc/openldap
	$(Q)echo "OpenLdap finish"

CLEAN_FILES = $(LDAP_SRCDIR)/$(LDAP_DIR) $(wildcard *.o)
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk

SDK_FEATURE_NAME = OpenLDAP
SDK_FILE_CP_LIST =  openldap-config/ldap.conf openldap-config/cacerts/client.pem Makefile *.tar.gz

include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
