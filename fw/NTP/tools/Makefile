-include $(PRJ_PATH)/.SDKPath
NTP_VERSION = ntp-4.2.8p3
NTP_BIN_DIR = $(PRJ_PATH)/NTP/bin
NTP_TOOL_ROOTDIR = $(PRJ_PATH)/NTP/tools
NTP_TOOL_DIR = $(PRJ_PATH)/NTP/tools/$(NTP_VERSION)
NTP_CFG = --with-yielding-select=yes \
		--with-openssl-libdir=$(PRJ_PATH)/OpenSSL/openssl \
		--with-openssl-incdir=$(PRJ_PATH)/OpenSSL/openssl


MY_CFG_HOST = arm-linux

ifeq ($(MYMCU),AST2050)
MY_CFG_HOST = arm-aspeed-linux-gnu
endif

ifeq ($(MYMCU),HERMON)
MY_CFG_HOST = arm-linux
endif

ifeq ($(MYMCU),YARKON)
MY_CFG_HOST = arm-none-linux-gnueabi
endif

override CFLAGS = -Os
override LDFLAGS =
override LIBS =
override INCLUDEDIR =

ntp_program:
	$(Q)echo "================ make NTP ==================="
	$(Q)if [ ! -d  $(NTP_TOOL_DIR) ];then \
	cd $(NTP_TOOL_ROOTDIR); tar -zxf $(NTP_VERSION).tar.gz ;fi
	$(Q)cd $(NTP_TOOL_DIR); ./configure --prefix=/local --host=$(MY_CFG_HOST) $(NTP_CFG); make -j; $(STRIP) ./ntpdate/ntpdate ;\
	$(STRIP) ./ntpd/ntpd; cp -f ./ntpdate/ntpdate $(NTP_BIN_DIR)/; cp -f ./ntpd/ntpd $(NTP_BIN_DIR)/
	$(Q)echo "================ make NTP done ==================="
