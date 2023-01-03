-include $(PRJ_PATH)/.SDKPath
HOST             = $(subst -gcc,,$(notdir $(CROSS_COMPILE)gcc))
SNMP_DIR         = $(PRJ_PATH)/SNMP
SNMP_VER         = 5.7.2.1
SNMP_PKG_NAME    = net-snmp-$(SNMP_VER)
SNMP_SRCDIR      = $(SNMP_DIR)/$(SNMP_PKG_NAME)
SNMP_INSTDIR     = $(SNMP_DIR)/SNMP_BIN
SNMP_ZIP         = $(wildcard $(SNMP_DIR)/*.tar.gz)
SNMP_CFG         = --prefix=${SNMP_INSTDIR}
SNMP_CFG_HOST    = --host=${HOST}
SNMP_IPMI_AGENT_LIB_NAME = ipmiAgentPluginObject
TARGET_SNMP_DIR = $(SNMP_DIR)/Host/$(MYMCU)/Board/$(BOARD)/
DEFAULT_SNMP_CONFIG = $(SNMP_DIR)/snmpd.conf
RM_TARGET = *.o *.so *.d
SNMP_CFG_FEATURE = \
--disable-applications \
--with-endianness=little \
--disable-manuals \
--disable-scripts \
--enable-ipv6 \
--disable-embedded-perl \
--without-perl-modules \
--enable-static=NO \
--with-openssl=$(PRJ_PATH)/OpenSSL/openssl/local \
--with-persistent-directory="/tmp/net-snmp" \
--with-default-snmp-version="3" \
--with-sys-contact="root$(Q)" \
--with-sys-location="Unknown" \
--with-logfile="/tmp/snmpd.log"
#--with-out-transports="Unix"
#--disable-debugging \
#--with-out-mib-modules="snmpv3mibs agentx agent_mibs disman/event disman/schedule utilities host examples/ucdDemoPublic examples/example mibII/mta_sendmail disman/old-event-mib ucd-snmp/lmSensors" \

DTKSNMP_DIR = $(DTKPATH)/SNMP
SNMP_INC_FLAG = -I$(SNMP_DIR)/$(SNMP_PKG_NAME)/include -I$(PRJ_PATH)/IPMI/IPMI_CMDS/Pef/inc
TMP_LDARGS := $(LDFLAGS) -L$(SNMP_INSTDIR)/lib -lnetsnmp -lnetsnmphelpers -lnetsnmpagent -lnetsnmpmibs

override CFLAGS += -Os
override LDFLAGS =
override LIBS =
override INCLUDEDIR =


all:

install:
	@echo "SRCDIR = $(SNMP_SRCDIR)"
	$(Q)set -e;if [ ! -d $(SNMP_SRCDIR) ]; then \
	cd $(SNMP_DIR); tar -zxvf $(SNMP_ZIP); \
	cd $(SNMP_SRCDIR); \
	./configure $(SNMP_CFG) $(SNMP_CFG_HOST) $(SNMP_CFG_FEATURE) ; \
	make ; \
	make install; fi;\
	cd $(SNMP_INSTDIR); \
	$(CROSS_COMPILE)strip sbin/*;
	$(Q)cp $(SNMP_INSTDIR)/sbin/snmpd $(FS_PATH)/sbin;
	$(Q)cp $(SNMP_SRCDIR)/net-snmp-config $(FS_PATH)/sbin;
	$(Q)cp $(SNMP_DIR)/.snmp_pkg/*.so $(SNMP_DIR)/
	$(Q)if [ ! -d $(FS_PATH)/usr/local/share/snmp/mibs ]; then mkdir -p $(FS_PATH)/usr/local/share/snmp/mibs; fi
	$(Q)cp $(SNMP_DIR)/net-snmpd 	$(FS_PATH)/etc/init.d/
	$(Q)chmod +x $(FS_PATH)/etc/init.d/net-snmpd
	$(Q)cp $(SNMP_DIR)/ATEN-IPMI-MIB $(FS_PATH)/usr/local/share/snmp/mibs/ATEN-IPMI-MIB.txt;
	$(Q)cp -f $(SNMP_DIR)/$(SNMP_IPMI_AGENT_LIB_NAME).so $(FS_PATH)/lib/
	$(Q)cp -f $(DEFAULT_SNMP_CONFIG) $(FS_PATH)/etc/defaults/ 
	$(Q)$(PRJ_PATH)/Tools/bin/dos2unix $(FS_PATH)/etc/defaults/snmpd.conf
	$(Q)cp -af $(SNMP_INSTDIR)/lib/* $(FS_PATH)/lib/

extract:
	$(Q)echo "******************** extract SNMP ********************"
	$(Q)if [ ! -d $(DTKSNMP_DIR) ];then mkdir -p $(DTKSNMP_DIR); fi
	$(Q)cp -f *.tar.gz Makefile *.o if_ether.h *.conf ATEN-IPMI-MIB $(DTKSNMP_DIR)/
	$(Q)mkdir -p $(DTKSNMP_DIR)/Host/$(MYMCU)/Board/$(BOARD)/; 
	$(Q)cp -af $(SNMP_DIR)/Host/$(MYMCU)/Board/$(BOARD)/* $(DTKSNMP_DIR)/Host/$(MYMCU)/Board/$(BOARD)/
	$(Q)cd $(SNMP_DIR); cat Makefile| sed \
	-e '/SDK/d' -e '/DTK/d' \
	-e '/extract/d' \
	-e '/cat Makefile|/d' \
	-e '/SNMP_INC_FLAG/d' \
	-e '/RM_TARGET/d' \
	-e "/-e [\'\"]/d" \
	> $(DTKSNMP_DIR)/Makefile
	$(Q)chmod 744 $(DTKSNMP_DIR)/Makefile


CLEAN_FILES = $(SNMP_SRCDIR)
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk
