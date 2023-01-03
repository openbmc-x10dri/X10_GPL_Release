BUSY_SRCDIR = $(PRJ_PATH)/busybox/
#BUSY_ZIP   = $(wildcard $(BUSY_SRCDIR)/*.tar.gz)
VER=1.23.1
BUSYBOX_SRC= $(BUSY_SRCDIR)/busybox-$(VER)
BUSY_ZIP   = $(BUSY_SRCDIR)/busybox-$(VER).tar.bz2
CONFIG_FILE_NAME = Host/$(MYMCU)/config


override CFLAGS = 
override LDFLAGS =


all:
	
install:
	$(Q)echo "******************** build busybox ********************"
#copy busybox
	$(Q)if [ ! -d $(BUSYBOX_SRC) ];then \
	 cd $(BUSYBOX_SRC);tar jxf $(BUSY_ZIP);fi
	$(Q)cp $(CONFIG_FILE_NAME) $(BUSYBOX_SRC)/.config
	$(Q)cd $(BUSYBOX_SRC); make -j; make install; cp -a _install/*  $(FS_PATH)/; 

CLEAN_FILES = $(BUSYBOX_SRC) busybox.log
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk

SDK_FEATURE_NAME = busybox
SDK_FILE_CP_LIST = ./Makefile ./busybox*.tar.gz ./Host/$(MYMCU)/config
include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
