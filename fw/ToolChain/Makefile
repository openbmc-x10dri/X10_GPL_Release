HOST = $(subst -gcc,,$(notdir $(CROSS_COMPILE)gcc))
LIBMQ_SRCDIR = $(PRJ_PATH)/ToolChain
LIBMQ_ZIP    = $(wildcard $(LIBMQ_SRCDIR)/*.tar.gz)
LIBMQ_CFG    = --host=${HOST}

override CFLAGS = 
override LDFLAGS = 
override LIBS =

all:
	$(Q)echo "******************** make libmqueue ********************"
	$(Q)cd $(LIBMQ_SRCDIR); \
	if [ ! -d lib_mq ];then mkdir lib_mq;cd lib_mq;tar zxf $(LIBMQ_ZIP);fi
	$(Q)cd $(LIBMQ_SRCDIR)/lib_mq/libmqueue-4.41; if [ ! -f Makefile ];then \
	./configure $(LIBMQ_CFG);make;fi
	$(Q)cp -a $(LIBMQ_SRCDIR)/lib_mq/libmqueue-4.41/src/.libs/*.so $(PRJ_PATH)/lib/
	$(Q)cp -a $(LIBMQ_SRCDIR)/lib_mq/libmqueue-4.41/src/.libs/*.so.* $(PRJ_PATH)/lib/
install:

	#******************************do nothing***************************

CLEAN_FILES = $(LIBMQ_SRCDIR)/lib_mq Host/$(MYMCU)/x-tools Host/i386/mingw32 Host/x86_64/mingw-w64
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk


SDK_FEATURE_NAME = ToolChain
SDK_FILE_CP_LIST = ./Makefile ./*.tar.gz ./Host/$(MYMCU)/*.tar.gz ./Host/i386/*.tar.gz ./Host/x86_64/*.tar.bz2



include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
