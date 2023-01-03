-include $(PRJ_PATH)/.SDKPath
HOST = $(subst -gcc,,$(notdir $(CROSS_COMPILE)gcc))
LIBNAME = libradius_client.so
DTKRADIUS_DIR = $(DTKPATH)/RADIUS

all:
	$(Q)echo "******************** make RADIUS ********************"
	${CC} -shared -o $(LIBPATH)/$(LIBNAME) -I. util.c md5.c dict.c radius_client.c
install:
	$(Q)echo "************** nothing to do *************"

CLEAN_FILES = radtest
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk
