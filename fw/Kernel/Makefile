-include $(PRJ_PATH)/.SDKPath
-include $(PRJ_PATH)/.config
-include $(PRJ_PATH)/.machine
include  $(PRJ_PATH)/PKConfig/Lx_Script/Makefile.lib

KERNEL_SRCDIR = $(PRJ_PATH)/Kernel/Host/$(MYMCU)
KERNEL_ZIP = $(wildcard $(KERNEL_SRCDIR)/*.tar.gz)

DTKKERNEL_DIR = $(DTKPATH)/Kernel

ifeq ($(MYMCU),$(filter $(MYMCU), AST2050 HERMON))
OBJCPY_ARG = .note
else
OBJCPY_ARG = .note.gnu.build-id
endif

override LDFLAGS =

all:
	$(Q)echo "Build Kernel ........"
	$(Q)cd $(KERNEL_SRCDIR);if [ ! -d $(KERNEL_SRCDIR)/linux ];then \
	mkdir linux;cd linux ;tar zxf $(KERNEL_ZIP);fi
ifeq ($(CONFIG_ECHI_DRV),y)
	$(Q)cp $(KERNEL_SRCDIR)/Board/$(BOARD)/config_usb $(KERNEL_SRCDIR)/linux/.config
else 
	$(Q)cp $(KERNEL_SRCDIR)/Board/$(BOARD)/config $(KERNEL_SRCDIR)/linux/.config
endif
ifeq ($(MYMCU),HERMON)
	$(Q)cp $(KERNEL_SRCDIR)/head.S $(KERNEL_SRCDIR)/linux/arch/arm/kernel
endif
ifeq ($(MYMCU),AST2050)
	cp $(KERNEL_SRCDIR)/Board/$(BOARD)/ftgmac100_26.[ch] $(KERNEL_SRCDIR)/linux/drivers/net
#Change Huawei Kernel Makefile toolchain version 
ifeq ($(BOARD),HW_STG2SMCA)
	cp -f $(KERNEL_SRCDIR)/Board/$(BOARD)/Makefile $(KERNEL_SRCDIR)/linux/
endif
endif
	$(Q)if [ -d $(KERNEL_SRCDIR)/patch ] && [ ! -f $(KERNEL_SRCDIR)/linux/.patch ];then \
	cp $(KERNEL_SRCDIR)/patch/*.patch $(KERNEL_SRCDIR)/linux;\
	cd $(KERNEL_SRCDIR)/linux;\
	for i in *.patch; do \
	patch -p1 < $$i;\
	done;\
	touch .patch;\
	fi
	$(Q)cd $(KERNEL_SRCDIR);cd linux;make ARCH=arm;
	$(call KENERL_MODULE_INSTALL,drivers/usb/host/ehci-hcd.ko)
	$(call KENERL_MODULE_INSTALL,drivers/mmc/host/ast_sdhci.ko)

install:
	$(Q)echo "Gen Kernel image....."	
	$(Q)cd $(KERNEL_SRCDIR)/linux;$(OBJCOPY) -O binary -R $(OBJCPY_ARG) \
	-R .comment -S vmlinux linux.bin;gzip -f -9 linux.bin
#	$(Q)cd $(KERNEL_SRCDIR)/linux;mkimage -A arm -O linux -T kernel \
#	-C gzip -a 40008000 -e 40008000 -d linux.bin.gz uImage
	$(Q)if [ ! -d $(IMAGE_PATH) ]; then \
	mkdir $(IMAGE_PATH); fi
ifneq ($(MYMCU),HERMON)
	$(Q)cp $(KERNEL_SRCDIR)/linux/linux.bin.gz $(IMAGE_PATH)/uImage.bin
else
	$(Q)cp $(KERNEL_SRCDIR)/image $(IMAGE_PATH)/image.bin
endif

CLEAN_FILES = $(KERNEL_SRCDIR)/linux $(KERNEL_SRCDIR)/image
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk


SDK_FEATURE_NAME = Kernel
SDK_FILE_CP_LIST = Host/$(MYMCU)/config Host/$(MYMCU)/head.S Host/$(MYMCU)/*.tar.gz \
					./Makefile  Host/$(MYMCU)/*.c  Host/$(MYMCU)/*.h \
					 Host/$(MYMCU)/patch/* Host/$(MYMCU)/Board/$(BOARD)/*

include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
