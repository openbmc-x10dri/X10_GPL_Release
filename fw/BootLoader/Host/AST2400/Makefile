-include $(PRJ_PATH)/.SDKPath
-include $(PRJ_PATH)/BootLoader/Host/$(MYMCU)/Board/$(BOARD)/config.mk
-include $(PRJ_PATH)/.config
SDKBL_DIR=$(SDKPATH)/BootLoader/Host/$(MYMCU)/


override CFLAGS = -Os 
override LDFLAGS =
override LIBS =
override INCLUDEDIR =

all:
ifeq ($(CONFIG_UBOOT_BUILD),y)
	$(Q)-rm ./build_tmp
	$(Q)if [ -d  $(BL_SRC_DIR) ]; then rm -rf $(BL_SRC_DIR); fi
endif
	$(Q)if [ ! -d  $(BL_SRC_DIR) ]; then tar -zxvf $(BL_TAR_BALL); fi
	$(Q)rm -f uboot
	$(Q)ln -s $(BL_SRC_DIR) uboot
	$(Q)if [ ! -f ./build_tmp ]; then cd $(BL_SRC_DIR)/; echo "CONFIG_HOST=$(CONFIG_HOST)"; make $(CONFIG_HOST); make -j;fi
	$(Q)touch ./build_tmp;
ifeq ($(CONFIG_UBOOT_BUILD),y)
	$(Q)echo "Update New U-BOOT............."
	$(Q)cp $(BL_SRC_DIR)/u-boot.bin ./u-boot.bin
endif
	$(Q)if [ -f ./u-boot.bin ]; then cp -f ./u-boot.bin $(PRJ_PATH)/MKIMG_Tool/Host/$(MYMCU)/Board/$(BOARD)/ ;\
	cp -f ./u-boot.bin $(IMAGE_PATH) ; fi
	$(Q)cp -af $(BL_SRC_DIR)/tools/env/fw_printenv $(PRJ_PATH)/bin
	$(Q)cp -af $(BL_SRC_DIR)/tools/env/fw_setenv $(PRJ_PATH)/bin
	$(Q)cp -af $(BL_SRC_DIR)/tools/env/*.a 		 $(PRJ_PATH)/lib
