-include $(PRJ_PATH)/.config
-include $(PRJ_PATH)/.machine
include $(PRJ_PATH)/PKConfig/Lx_Script/Makefile.lib

TOOL_PATH   = $(PRJ_PATH)/MKIMG_Tool/Host/$(MYMCU)/Board/$(BOARD)
BOARD_PATH  = $(PRJ_PATH)/MKIMG_Tool/Host/$(MYMCU)/
SRC_PATH  = $(PRJ_PATH)/MKIMG_Tool
WORK_PATH   = $(PRJ_PATH)/MKIMG_Tool/tmp
MKIMAGE_FILE_PATH = $(PRJ_PATH)/BootLoader/Host/$(MYMCU)/uboot/tools/mkimage

HOST_CC    = gcc 
#HOST_CC_CFLAG    = $(call CHECK_CC_RULE,-fno-stack-protector)
DTKMKIMG_DIR = $(DTKPATH)/MKIMG_Tool

#bootloader MYMCUTYPE 
ifeq ($(MYMCU),HERMON)
# HERMON
MYMCUTYPE=0
else 
# AST2050 YARKON PILOT3 AST2300
ifeq ($(MYMCU),AST2400)
MYMCUTYPE=2
HOST_CC_CFLAG += $(FLASH_LAYOUT_FLAGS)
HOST_CC_CFLAG += -I$(PRJ_PATH)/MKIMG_Tool/Host/$(MYMCU)/Board/$(BOARD)
UBOOT_ENV_DEFINED = $(PRJ_PATH)/BootLoader/Host/$(MYMCU)/uboot/include
else
MYMCUTYPE=1
HOST_CC_CFLAG += $(FLASH_LAYOUT_FLAGS)
HOST_CC_CFLAG += -I$(PRJ_PATH)/MKIMG_Tool/Host/$(MYMCU)/Board/$(BOARD)
UBOOT_ENV_DEFINED = $(PRJ_PATH)/BootLoader/Host/$(MYMCU)/uboot/include
endif
endif
FWVERSION=$(ver)
#IMAGE_PATH

install:
	$(Q)if [ -d $(WORK_PATH) ];then rm -rf $(WORK_PATH); fi
	$(Q)mkdir $(WORK_PATH);
	$(Q)$(ECHO_CMD) "Copy mkbin"
	$(Q)cp -af $(SRC_PATH)/.mkimg_pkg/mkbin $(WORK_PATH)/
	$(Q)cd $(IMAGE_PATH); mv uImage.bin kernel.bin;
	$(Q)$(ECHO_CMD) "produce uboot env image"
	$(Q)cp -af $(SRC_PATH)/.mkimg_pkg/mk_uboot_env_img $(WORK_PATH)
	$(Q)cp $(MKIMAGE_FILE_PATH) $(WORK_PATH)/ -rf
	$(Q)cp $(TOOL_PATH)/* $(WORK_PATH)/ -rf
	$(Q)cp $(IMAGE_PATH)/* $(WORK_PATH)/ -rf
	$(Q)cd ${WORK_PATH};sh ${WORK_PATH}/cmd_script.sh;if [ $$? -ne 0 ];then exit 1;fi
	$(Q)if [ ! -z  $(IMAGE_PATH) ] && [ -d  $(IMAGE_PATH) ] ;then \
	rm -f $(IMAGE_PATH)/*; \
	cd ${WORK_PATH};cp *.bin $(IMAGE_PATH)/; fi
	$(Q)rm -rf $(WORK_PATH)
ifneq ($(CONFIG_EXTRACT_MOD),y)
ifeq ($(MYMCU),AST2050)
# except IP1500, ADLink, Nexcom
#ifneq ($(BOARD), $(filter $(BOARD),IP1500 ADLINK_CMM NEXCOM_NSB7110))
ifeq ($(BOARD),AST2050_EVB)
	$(Q)bash $(PRJ_PATH)/PKConfig/MDInfo/mdinfo.sh $(MYMCUTYPE) $(PRJ_PATH)/FileSystem/Host/$(MYMCU)/Board/$(BOARD)
endif
endif
ifeq ($(MYMCU),HERMON)
	$(Q)bash $(PRJ_PATH)/PKConfig/MDInfo/mdinfo.sh $(MYMCUTYPE) $(PRJ_PATH)/FileSystem/Host/$(MYMCU)/Board/$(BOARD)
endif
ifeq ($(MYMCU),AST2400)
	$(Q)bash $(PRJ_PATH)/PKConfig/MDInfo/mdinfo.sh $(MYMCUTYPE) $(PRJ_PATH)/FileSystem/Host/$(MYMCU)/Board/$(BOARD)
endif
endif
CLEAN_PATTERN = '*.o'
CLEAN_FILES = $(WORK_PATH) $(TOOL_PATH)/mkimage \
            $(call GEN_SEARCH_LIST,$(CLEAN_PATTERN),$(SRC_PATH),,) \
            $(call GEN_SEARCH_LIST,$(CLEAN_PATTERN),$(BOARD_PATH),,)
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk

DEFAULT_PATTERN += '*.bin' '*.sh' '*.inf' '*.o'
include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
