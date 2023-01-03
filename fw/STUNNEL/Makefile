-include $(PRJ_PATH)/.SDKPath
SRCDIR = $(PRJ_PATH)/STUNNEL/stunnel-*
DSTDIR = $(PRJ_PATH)/STUNNEL/stunnel
STUNNEL_ZIP = $(PRJ_PATH)/STUNNEL/stunnel-*.tar.gz
HOST = $(subst -gcc,,$(notdir $(CROSS_COMPILE)gcc))
STUNNEL_CONF = --host=$(HOST) \
--with-ssl=$(PRJ_PATH)/OpenSSL/openssl/local \
--disable-fips \
--prefix=$(DSTDIR)

CFLAGS        += -fno-stack-protector 
override CPPFLAGS      =
override LDFLAGS       =
override LIBS          =


all:
install:
	@echo "*************Build Stunnel Begin******************"
	if [ ! -d $(SRCDIR) ];then \
	tar zxf $(STUNNEL_ZIP); \
	mkdir $(DSTDIR); fi
	cd $(SRCDIR); \
	./configure $(STUNNEL_CONF); \
	make; \
	make install;
	rm $(DSTDIR)/etc/stunnel/*.pem;
	rm $(DSTDIR)/etc/stunnel/*.conf-sample;
	rm -rf $(DSTDIR)/share;
	rm -rf $(DSTDIR)/var;
	cp -af $(PRJ_PATH)/STUNNEL/stunnel.conf $(DSTDIR)/etc/stunnel/stunnel.conf;
	cp -af $(PRJ_PATH)/STUNNEL/mail.pem $(DSTDIR)/etc/stunnel/mail.pem;
	cp -af $(DSTDIR)/* $(FS_PATH);
	cp -af $(PRJ_PATH)/STUNNEL/stunneld $(FS_PATH)/etc/init.d/;
	chmod +x $(FS_PATH)/etc/init.d/stunneld
	@echo "*************Build Stunnel End******************"
	
CLEAN_FILES =  $(SRCDIR)/ $(DSTDIR)
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk


