-include $(PRJ_PATH)/.SDKPath
HOST = $(subst -gcc,,$(notdir $(CROSS_COMPILE)gcc))
SMTP_SRCDIR = $(PRJ_PATH)/SMTP
SMTP_VER    = 1.4.32
SMTP_ZIP    = msmtp-$(SMTP_VER).tar.bz2
SMTP_DIR    = $(SMTP_SRCDIR)/msmtp-$(SMTP_VER)
SMTP_CFG    = --host=${HOST} -with-ssl=openssl --libdir=$(PRJ_PATH)/OpenSSL/openssl/local/lib --without-libidn
DTKSMTP_DIR = $(DTKPATH)/SMTP

libssl_CFLAGS=-I$(PRJ_PATH)/OpenSSL/openssl/local/include 
libssl_LIBS=-lssl -lcrypto -L$(PRJ_PATH)/OpenSSL/openssl/local/lib
export libssl_CFLAGS libssl_LIBS
override CFLAGS = 
override LDFLAGS = 
override LIBS =

all:
	$(Q)cd $(SMTP_SRCDIR); \
	if [ ! -d $(SMTP_DIR) ];then tar jxf $(SMTP_ZIP);fi
	$(Q)cd $(SMTP_DIR);if [ ! -f $(SMTP_DIR)/src/msmtp ];then \
	./configure $(SMTP_CFG);make;fi
	$(Q)$(CROSS_COMPILE)strip $(SMTP_DIR)/src/msmtp
	$(Q)cp $(SMTP_DIR)/src/msmtp $(BINPATH)/msmtp
install:
	
CLEAN_FILES = $(SMTP_DIR)
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk

#================= SDK param  ===================
SDK_FEATURE_NAME = SMTP
SDK_FILE_CP_LIST = ./Makefile  ./msmtp-1.4.16.tar.gz  ./ReadMe ./smtpclient.sh
#================= end of SDK param ===================

include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
