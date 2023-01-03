-include $(PRJ_PATH)/.SDKPath
CIMOM_SUITE_DIR = $(PRJ_PATH)/SFCB
CB_ROOT_DIR = $(PRJ_PATH)/SFCB
SFCB_BUILD_DIR = $(PRJ_PATH)/SFCB/build_sfcbarm
SFCBx86_BUILD_DIR =$(PRJ_PATH)/SFCB/build_sfcbx86
SFCB_VERSION = 1.3.8
SFCB_DIR = $(CB_ROOT_DIR)/sblim-sfcb-$(SFCB_VERSION)
ZLIB_DIR = $(CB_ROOT_DIR)/zlib-1.2.3
SFCC_ROOT_DIR = $(PRJ_PATH)/SFCC
CURL_VERIOSN  = 7.18.1
CURL_BUILD_DIR = $(SFCC_ROOT_DIR)/build_curl
CURL_X86_DIR = $(SFCC_ROOT_DIR)/build_curlx86
CURL_SRC_DIR =$(SFCC_ROOT_DIR)/curl-$(CURL_VERIOSN)
PROVIDER_SRC_DIR = $(CB_ROOT_DIR)/providers
DOS2UNIX_DIR = $(PRJ_PATH)/Tools/bin/


export SFCB_DIR SFCB_BUILD_DIR
CMPI_BASE_DIR = $(PROVIDER_SRC_DIR)/sblim-cmpi-base-1.5.7

LOG_RECORD_DIR = $(PROVIDER_SRC_DIR)/LogRecord
THRESHOLD_SENSOR_DIR = $(PROVIDER_SRC_DIR)/ThresholdSensor
DISCRETE_SENSOR_DIR = $(PROVIDER_SRC_DIR)/DiscreteSensor
RECORD_LOG_DIR = $(PROVIDER_SRC_DIR)/RecordLog
POWER_CONTROL_DIR = $(PROVIDER_SRC_DIR)/PowerControl
SOFTWARE_INSTALLATION_DIR = $(PROVIDER_SRC_DIR)/SoftwareInstallationService
TEXT_CONSOLE_DIR = $(PROVIDER_SRC_DIR)/TextRedirection
BMC_FIRMWARE_DIR = $(PROVIDER_SRC_DIR)/BMCFirmware

SFCB_STAGE_DIR = $(SFCB_BUILD_DIR)/var/lib/sfcb/stage
SFCB_CIMOM_DIR = $(SFCB_BUILD_DIR)/share/sfcb/CIM
SFCB_REG_DIR   = $(SFCB_BUILD_DIR)/var/lib/sfcb/registration

ifeq ($(MYMCU), AST2050)
SFCB_CFLAGS = "-DHOST_NAME_MAX=64 -Os"
else 
SFCB_CFLAGS = -Os
endif 

CFG_SFCB_PRF = \
--prefix=$(SFCB_BUILD_DIR)/ \
--sysconfdir=/etc/ \
CIMSCHEMA_SOURCE="$(CB_ROOT_DIR)/cim_schema_2.26.0Final-MOFs.zip" \
CIMSCHEMA_MOF=cim_schema_2.26.0.mof \
CIMSCHEMA_SUBDIRS=true

CFG_SFCB_X86_PRF = \
--prefix=$(SFCBx86_BUILD_DIR)/ \
CIMSCHEMA_SOURCE="$(CB_ROOT_DIR)/cim_schema_2.26.0Final-MOFs.zip" \
CIMSCHEMA_MOF=cim_schema_2.26.0.mof \
CIMSCHEMA_SUBDIRS=true \
--build=i686-pc-linux-gnu \
--host=i686-pc-linux-gnu \
CC=gcc \
AR=ar \
RANLIB=ranlib \
STRIP=strip \
CXX=g++ \
LD=ld \
NM=nm

CURL_CFG =\
--disable-largefile \
--disable-ftp \
--disable-file \
--disable-ldap \
--disable-ldaps \
--disable-dict \
--disable-telnet \
--disable-tftp \
--disable-manual \
--disable-ipv6 \
--disable-verbose \
--disable-sspi \
--disable-debug \
--disable-cookies \
--with-pic \
--without-libssh2 \
--without-gnutls \
--without-nss \
--without-ca-bundle \
--without-ca-path \
--without-libidn

CFG_FEATURE =

HOST = arm-linux
CFG_HOST = --host=$(HOST)

LIBS=
.PHONY: build_curl_x86 build_zlib build_sblim_sfcb_x86 build_sblim_sfcb_arm build_MOF build_provider build_sfcb_allpackage 
all:

install:
	$(Q)echo "**********************Build curlx86*****************************"
	make build_curl_x86
	if [ ! -d $(ZLIB_DIR) ];then make build_zlib;fi
	$(Q)echo "***************************Build SFCB***************************"
	cd $(CB_ROOT_DIR);
	if [ ! -d $(SFCB_DIR) ];then \
	cd $(CB_ROOT_DIR); tar jxf sblim-sfcb-$(SFCB_VERSION).tar.bz2 ; fi
	if [ ! -d $(SFCB_BUILD_DIR) ];then \
	make build_sfcb_allpackage; \
	fi
	$(Q)echo "*************************Install Providers*************************"
	if [ ! -d $(SFCB_BUILD_DIR)/lib/cmpi ];then mkdir -p $(SFCB_BUILD_DIR)/lib/cmpi; fi
	make build_provider
	$(Q)echo "************************Copy SFCB files ************************"
	chmod 777 -R $(SFCB_BUILD_DIR) $(ZLIB_DIR)/zlib $(CURL_BUILD_DIR);
	cp -af $(ZLIB_DIR)/zlib/lib $(FS_PATH)
	rm -rf $(SFCB_BUILD_DIR)/share/sfcb/CIM/* $(SFCB_BUILD_DIR)/share/doc $(SFCB_BUILD_DIR)/share/man \
	$(SFCB_BUILD_DIR)/var/lib/sfcb/registration/repository.previous/* $(SFCB_BUILD_DIR)/etc/sfcb/*.cfg  \
	$(SFCB_BUILD_DIR)/share/doc $(SFCB_BUILD_DIR)/bin/ ;
	cp -af $(SFCB_BUILD_DIR)/* $(FS_PATH)/;
	if [ ! -d $(FS_PATH)/etc/sfcb/ ];then mkdir -p $(FS_PATH)/etc/sfcb/ ;fi;cp -af $(CIMOM_SUITE_DIR)/conf/sfcb.cfg  $(FS_PATH)/etc/sfcb/;
	$(DOS2UNIX_DIR)/dos2unix $(FS_PATH)/etc/sfcb/sfcb.cfg 
	chmod a+x $(CIMOM_SUITE_DIR)/conf/sfcb;cp -af $(CIMOM_SUITE_DIR)/conf/sfcb  $(FS_PATH)/etc/init.d/;



build_curl_x86:
	if [ -f $(CURL_SRC_DIR)/Makefile ];then \
	cd $(CURL_SRC_DIR); \
	make clean; make distclean; \
	fi
	if [ ! -d $(CURL_X86_DIR) ];then \
	cd $(CURL_SRC_DIR); \
	CC=gcc AR=ar OBJDUMP=objdump RANLIB=ranlib STRIP=strip CFLAGS="-D_GNU_SOURCE" CPPFLAGS="-D_GNU_SOURCE" LDFLAGS="" ./configure --prefix=$(CURL_X86_DIR) $(CURL_CFG); \
	make -j; make install; \
	make clean; make distclean; \
	fi
build_zlib:
	cd $(CB_ROOT_DIR); tar zxvf zlib-1.2.3.tar.gz; 
	$(Q)echo "***************************Build zlib_arm***************************";
	cd $(ZLIB_DIR); CC=$(HOST)-gcc AR="$(HOST)-ar cr" CFLAGS="-Os -D_GNU_SOURCE" ./configure -s --prefix=./zlib;make -j;make install;make clean;make distclean; 
	cd $(ZLIB_DIR); $(STRIP) ./zlib/lib/libz.so.*; rm -rf ./zlib/share/man; 
	$(Q)echo "***************************Build zlib_x86***************************";
	cd $(ZLIB_DIR); CC=gcc AR="ar cr" CFLAGS="-Os -D_GNU_SOURCE" ./configure -s --prefix=./zlibx86; make -j;make install; 
	
	
build_sblim_sfcb_x86:
	cd $(SFCB_DIR); ./configure CFLAGS="-Os -D_GNU_SOURCE" CPPFLAGS="-I$(ZLIB_DIR)/zlibx86/include -I$(CURL_X86_DIR)/include" LDFLAGS="-L$(ZLIB_DIR)/zlibx86/lib -L$(CURL_X86_DIR)/lib" $(CFG_SFCB_X86_PRF); 
	cd $(SFCB_DIR); make ; 
	cd $(SFCB_DIR); make install; 
	cd $(SFCB_DIR); make install-strip; 
	cd $(SFCB_DIR); make postinstall; 
	cd $(SFCB_DIR); make clean; 
	cd $(SFCB_DIR); make distclean; 

build_sblim_sfcb_arm:
	cd $(SFCB_DIR); ./configure CFLAGS=$(SFCB_CFLAGS) CPPFLAGS="-I$(ZLIB_DIR)/zlib/include -I$(CURL_BUILD_DIR)/include" LDFLAGS="-L$(ZLIB_DIR)/zlib/lib -L$(CURL_BUILD_DIR)/lib" $(CFG_SFCB_PRF) $(CFG_HOST); 
	cd $(SFCB_DIR); sed -e "/^SUBDIRS.*=/d" -i Makefile; 
	cd $(SFCB_DIR); make ; 
	cd $(SFCB_DIR); make install; 
	cd $(SFCB_DIR); make install-strip; 
	cd $(SFCB_DIR); make postinstall; 
	
build_MOF:
	export PATH=$(SFCBx86_BUILD_DIR)/bin:$(SFCBx86_BUILD_DIR)/sbin:$(PATH);\
	cd $(LOG_RECORD_DIR); \
	sh provider-register.sh -t sfcb -r mof/IPMI_LogRecord.registration -m mof/IPMI_LogRecord.mof -s $(SFCB_STAGE_DIR) -c $(SFCB_CIMOM_DIR)  -i $(SFCB_REG_DIR);\
	cd $(THRESHOLD_SENSOR_DIR); \
	sh provider-register.sh -t sfcb -r mof/Threshold_Sensor.registration -m mof/Threshold_Sensor.mof -s $(SFCB_STAGE_DIR) -c $(SFCB_CIMOM_DIR)  -i $(SFCB_REG_DIR);\
	cd $(RECORD_LOG_DIR); \
	sh provider-register.sh -t sfcb -r mof/IPMI_RecordLog.registration -m mof/IPMI_RecordLog.mof -s $(SFCB_STAGE_DIR) -c $(SFCB_CIMOM_DIR)  -i $(SFCB_REG_DIR);\
	cd $(DISCRETE_SENSOR_DIR); \
	sh provider-register.sh -t sfcb -r mof/Discrete_Sensor.registration -m mof/Discrete_Sensor.mof -s $(SFCB_STAGE_DIR) -c $(SFCB_CIMOM_DIR)  -i $(SFCB_REG_DIR);\
	cd $(POWER_CONTROL_DIR); \
	sh provider-register.sh -t sfcb -r mof/IPMI_PowerManagementService.registration -m mof/IPMI_PowerManagementService.mof -s $(SFCB_STAGE_DIR) -c $(SFCB_CIMOM_DIR)  -i $(SFCB_REG_DIR);\
	cd $(SOFTWARE_INSTALLATION_DIR); \
	sh provider-register.sh -t sfcb -r mof/IPMI_SoftwareInstallationService.registration -m mof/IPMI_SoftwareInstallationService.mof -s $(SFCB_STAGE_DIR) -c $(SFCB_CIMOM_DIR)  -i $(SFCB_REG_DIR);\
	cd $(TEXT_CONSOLE_DIR); \
	sh provider-register.sh -t sfcb -r mof/IPMI_TextRedirectionService.registration -m mof/IPMI_TextRedirectionService.mof -s $(SFCB_STAGE_DIR) -c $(SFCB_CIMOM_DIR)  -i $(SFCB_REG_DIR);\
	cd $(BMC_FIRMWARE_DIR); \
	sh provider-register.sh -t sfcb -r mof/IPMI_SoftwareIdentity.registration -m mof/IPMI_SoftwareIdentity.mof -s $(SFCB_STAGE_DIR) -c $(SFCB_CIMOM_DIR)  -i $(SFCB_REG_DIR);

build_provider:
	cp -af providers/cmpi/*.so* $(SFCB_BUILD_DIR)/lib/cmpi/

build_sfcb_allpackage:
	$(Q)echo "***************************Build x86 SFCB***************************"; 
	make build_sblim_sfcb_x86; 
	$(Q)echo "***************************Build ARM SFCB***************************"; 
	make build_sblim_sfcb_arm; 
	$(Q)echo "*************************Build MOF*************************"; 
	make build_MOF; 

	

CLEAN_PATTERN = '*.o' '*.d' '*.so*'	
CLEAN_FILES =$(SFCBx86_BUILD_DIR) $(ZLIB_DIR) $(CMPI_BASE_DIR) \
			 $(SFCB_DIR) $(SFCB_BUILD_DIR) $(CURL_X86_DIR) $(DOS2UNIX_DIR)\
			 $(call GEN_SEARCH_LIST,$(CLEAN_PATTERN),$(LOG_RECORD_DIR),,) \
			 $(call GEN_SEARCH_LIST,$(CLEAN_PATTERN),$(THRESHOLD_SENSOR_DIR),,) \
			 $(call GEN_SEARCH_LIST,$(CLEAN_PATTERN),$(DISCRETE_SENSOR_DIR),,) \
			 $(call GEN_SEARCH_LIST,$(CLEAN_PATTERN),$(RECORD_LOG_DIR),,) \
			 $(call GEN_SEARCH_LIST,$(CLEAN_PATTERN),$(POWER_CONTROL_DIR),,) \
			 $(call GEN_SEARCH_LIST,$(CLEAN_PATTERN),$(SOFTWARE_INSTALLATION_DIR),,) \
			 $(call GEN_SEARCH_LIST,$(CLEAN_PATTERN),$(TEXT_CONSOLE_DIR),,) \
			 $(call GEN_SEARCH_LIST,$(CLEAN_PATTERN),$(BMC_FIRMWARE_DIR),,)

include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk
	
include $(PRJ_PATH)/PKConfig/Lx_Script/Makefile.lib

SDK_FEATURE_NAME = SFCB
PATTERN = '*.c' '*.h' '*.sh' '*.mof' '*.registration' 'Makefile'
SDK_FILE_CP_LIST = $(call GEN_SEARCH_LIST,$(PATTERN),providers/,,)
SDK_FILE_CP_LIST += zlib-1.2.3.tar.gz  *.tar.bz2 *.tar.gz Makefile \
					cim_schema_2.26.0Final-MOFs.zip conf/sfcb conf/sfcb.cfg 
					

include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
