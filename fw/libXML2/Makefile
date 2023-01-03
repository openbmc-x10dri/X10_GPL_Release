-include $(PRJ_PATH)/.SDKPath
include $(PRJ_PATH)/PKConfig/Lx_Script/Makefile.lib
HOST = $(subst -gcc,,$(notdir $(CROSS_COMPILE)gcc))
LIBXML2_DIR = $(PRJ_PATH)/libXML2/libxml2/libxml2-2.6.32
unexport CC LD AR CXX NM RANLIB OBJCOPY OBJDUMP \
STRIP CFLAGS LDFLAGS LIBS

XML2_CFG = --prefix=$$PWD/../local  --host=$(HOST)  CFLAGS=" -Os "\
--enable-ipv6=no \
--with-pic \
--without-c14n \
--without-debug \
--without-docbook \
--without-ftp \
--without-history \
--without-html \
--without-http \
--without-iso8859x \
--without-legacy \
--without-mem-debug \
--without-run-debug \
--without-valid \
--without-xinclude \
--without-python 

DTKlibXML2_DIR = $(DTKPATH)/libXML2

all:
	@echo "Build libxml2 ........"
	$(Q)if [ ! -d $(LIBXML2_DIR)/../local ]; then \
	tar zxf libxml2.tar.gz ;\
	cd $(LIBXML2_DIR); ./configure $(XML2_CFG) ; \
	make -j; make install; make install-strip;\
	fi
	$(Q)$(CP_CMD) $(LIBXML2_DIR)/../local/lib/*.so $(PRJ_PATH)/lib
	$(Q)cd $(PRJ_PATH)/lib/;if [ ! -f libxml2.so.2 ];then ln -s libxml2.so libxml2.so.2;fi
	$(Q)if [ ! -d $(TC_LOCAL)/lib/pkgconfig/ ];then $(MKDIR_CMD) -p  $(TC_LOCAL)/lib/pkgconfig/;fi
	$(Q)$(CP_CMD) $(LIBXML2_DIR)/../local/lib/pkgconfig/*.pc $(TC_LOCAL)/lib/pkgconfig/
install:
	#******************************do nothing***************************

CLEAN_FILES = libxml2/
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk

SDK_FEATURE_NAME = libXML2
SDK_FILE_CP_LIST = *.tar.gz  Makefile

include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
