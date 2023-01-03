-include $(PRJ_PATH)/.config
SHELLDST=$(PRJ_PATH)/SMASH/shell/buil_shell
HOST = $(subst -gcc,,$(notdir $(CROSS_COMPILE)gcc))
FLEX_VERSION = 2.5.35
FLEXSRC_DIR = $(PRJ_PATH)/SMASH/shell/flex-$(FLEX_VERSION)
READLINE_VERSION = 5.2
READLINE_DIR = $(PRJ_PATH)/SMASH/shell/readline-$(READLINE_VERSION)
TERMCAP_VERSION = 1.3.1
TERMCAP_DIR = $(PRJ_PATH)/SMASH/shell/termcap-$(TERMCAP_VERSION)

LDFLAGS += -lldap_client -L$(PRJ_PATH)/OpenSSL/openssl/local/lib/ -lssl -lcrypto 
CFLAGS+=-g -Wall -I$(SHELLDST)/include -I$(PRJ_PATH)/SMASH/shell -Os  -DSMASH_VERSION=\"$(SMASH_VERSION)\"

.PHONY: build_flex build_readline build_termcap

all:
	$(Q)echo "*************Build shell library******************"
	if [ ! -d $(FLEXSRC_DIR) ];then make build_flex;fi 
	if [ ! -d $(READLINE_DIR) ];then make build_readline;fi
	if [ ! -d $(TERMCAP_DIR) ];then make build_termcap;fi
	$(Q)echo "*************copy shell library******************"
	$(STRIP) --strip-unneeded $(SHELLDST)/lib/*.so*;
	cp -df $(SHELLDST)/lib/libreadline.so $(FS_PATH)/lib;
	cp -df $(SHELLDST)/lib/libreadline.so.5 $(FS_PATH)/lib;
	cp -df $(SHELLDST)/lib/libreadline.so.5.2 $(FS_PATH)/lib;
	
build_flex:
	tar zxf flex-$(FLEX_VERSION).tar.gz; 
	cd $(FLEXSRC_DIR); ./configure --host=$(HOST) --prefix=$(SHELLDST) CC=$(CC); 
	cd $(FLEXSRC_DIR); cp -af config.h_bak config.h;
	cd $(FLEXSRC_DIR); make -j && make install;
	
build_readline:
	tar zxf readline-$(READLINE_VERSION).tar.gz; 
	cd $(READLINE_DIR); ./configure --host=$(HOST) --prefix=$(SHELLDST) CC=$(CC) --disable-static ;
	cd $(READLINE_DIR);	make -j; 
	cd $(READLINE_DIR); rm -rf doc; 
	cd $(READLINE_DIR);make install; 

build_termcap:
	tar zxf termcap-$(TERMCAP_VERSION).tar.gz; 
	cd $(TERMCAP_DIR); ./configure --host=$(HOST) --prefix=$(SHELLDST) CC=$(CC); 
	cd $(TERMCAP_DIR); make -j && make install

