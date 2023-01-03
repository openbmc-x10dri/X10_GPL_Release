-include $(PRJ_PATH)/.config
-include $(PRJ_PATH)/.machine
SDRFiles = $(sort $(wildcard SDRFiles/SDRBlock* SDRFiles/SDRBlock.N*))
FRUFiles = FRUBlock
XMLFiles = $(wildcard defaults/*.xml conf/version.xml) 
CONFPath = $(FS_PATH)/etc/conf/
ETCPath  = $(FS_PATH)/etc/
BINPath  = $(FS_PATH)/bin/

.PHONY: validate_XML
validate_XML:
	$(Q)set -e ;for i in $(XMLFiles) ;do \
		xmllint --noout $$i; \
		if [ $$? -ne 0 ];then echo $$i"is corrupted!";exit 1 ;fi; \
		done

install:
	$(Q)mkdir -p  $(CONFPath)
#SDR files
	$(Q)cp $(SDRFiles) $(CONFPath)
#XML files
	if [ -f /usr/bin/xmllint ];then make validate_XML;fi 
	$(Q)cp $(XMLFiles)  $(CONFPath)
#FRU files
	$(Q)cp $(FRUFiles) $(CONFPath)
#IPV6 related files
	$(Q)mkdir -p $(FS_PATH)/etc/network
	$(Q)cp netconfig 	 $(ETCPath)/network/netconfig.default
	$(Q)cp udev  	 	 $(ETCPath)/init.d/
	$(Q)cp 99misc.sh  	 $(ETCPath)/init.d/
	$(Q)cp 10fw_env.sh	 $(ETCPath)/init.d/
	$(Q)cp fullspeed.sh	 $(BINPath)
	$(Q)cp modules  	 $(ETCPath)
	$(Q)ln -sf /nv/network/netconfig0 $(ETCPath)/network/netconfig0
	$(Q)ln -sf /nv/network/netconfig1 $(ETCPath)/network/netconfig1
	$(Q)ln -sf /nv/network/netconfig2 $(ETCPath)/network/netconfig2
	$(Q)cp network6 $(ETCPath)/network/
	$(Q)cp $(PRJ_PATH)/Kernel/Host/$(MYMCU)/linux/drivers/net/bonding/bonding.ko $(FS_PATH)/bin/module/
#default XML conifg
	$(Q)mkdir -p $(ETCPath)/defaults
	$(Q)cp defaults/*.xml    $(ETCPath)/defaults/
	$(Q)cp defaults/*.conf   $(ETCPath)/defaults/
	$(Q)mkdir -p 			 $(ETCPath)/scripts/
	$(Q)cp service  		 $(ETCPath)/scripts/
	$(Q)cp check_web_conf.sh $(ETCPath)/scripts/
ifeq ($(CONFIG_SWICTH_MODE_FROM_MAGIC_STR),y)
	$(Q)cp defaults/factory_uart.xml  $(ETCPath)/defaults/factory.xml
endif
	$(Q)cp defaults/*.config  $(ETCPath)/defaults/
	$(Q)cp ResetIP.sh 	   	  $(ETCPath)
	$(Q)if [ -f profile ]; then \
	cp profile $(ETCPath); \
	fi
#UPNP
ifeq ($(CONFIG_UPNP),y)
	$(Q)cp IPMIdevicedesc_sample.xml $(ETCPath)
endif
	$(Q)ln -sf /nv/hostname_for_dhcp $(ETCPath)/hostname_for_dhcp
ifeq ($(CONFIG_PLATFORM_JBOD),y)	
	$(Q)cp defaults/platform_jbod.conf  $(ETCPath)/platform.conf
endif
