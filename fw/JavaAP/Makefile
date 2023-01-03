JAVAAP_DIR         = $(PRJ_PATH)/JavaAP
JAVA_TOOLCHAIN_ZIP = jdk1.6.0_14.tar.gz
JAVA_HOME          = $(JAVAAP_DIR)/jdk1.6.0_14
JAVA_BIN           = $(JAVA_HOME)/bin
JAVAC              = $(JAVA_BIN)/javac
JAR                = $(JAVA_BIN)/jar
KEYTOOL            = $(JAVA_BIN)/keytool
JARSIGNER          = $(JAVA_BIN)/jarsigner
PACK200            = $(JAVA_BIN)/pack200
JAVA_INCLUDE       = $(JAVA_HOME)/include
JAVA_INCLUDE_WIN32 = $(JAVA_INCLUDE)/win32
JAVA_INCLUDE_LINUX = $(JAVA_INCLUDE)/linux
KEYSTORE           = $(JAVAAP_DIR)/SMCKeyStore.dat
MANIFEST		   = $(JAVAAP_DIR)/MYMANIFEST.MF
STOREPASS          = SuperSMC4Cert
KEYPASS            = SuperSMC4Cert
TIME_SERVER		   = https://timestamp.geotrust.com/tsa
PROVIDER           = smccert
ANT_ZIP            = apache-ant-1.7.1-bin.tar.gz
ANT_HOME           = $(JAVAAP_DIR)/apache-ant-1.7.1
ANT_BIN            = $(ANT_HOME)/bin
ANT                = $(ANT_BIN)/ant
CN                 = www.supermicro.com 
OU                 = SW
C                  = US
SDKJavaAP_DIR      = $(SDKPATH)/JavaAP
EXPIRE_DAYS		   = 1095
include $(PRJ_PATH)/ProjectConfig-JavaAP

export JAVAC JAR JARSIGNER PACK200 JAVA_INCLUDE JAVA_INCLUDE_WIN32 JAVA_INCLUDE_LINUX KEYSTORE STOREPASS KEYPASS PROVIDER ANT MANIFEST TIME_SERVER

all:

init_jdk:
	$(Q)if [ ! -d $(JAVA_HOME) ]; then cd $(JAVAAP_DIR); tar -zxf $(JAVA_TOOLCHAIN_ZIP); fi

init_ant:
	$(Q)if [ ! -d $(ANT_HOME) ]; then cd $(JAVAAP_DIR); tar -zxf $(ANT_ZIP); fi

genkey: 
	$(Q)if [ ! -f $(KEYSTORE) ]; then cd $(JAVAAP_DIR); $(KEYTOOL) -genkey -dname "CN=$(CN), OU=$(OU), C=$(C)" -alias $(PROVIDER) -keystore $(KEYSTORE) -storepass $(STOREPASS) -keypass $(KEYPASS) -validity $(EXPIRE_DAYS); fi

install: init_jdk init_ant 
	$(Q)$(MAKE) install -C KVM;
	$(Q)$(MAKE) install -C SOL;

clean:
#	$(Q)rm -rf $(KEYSTORE);
	$(Q)rm -rf $(ANT_HOME);
	$(Q)rm -rf $(JAVA_HOME);
	$(Q)$(MAKE) clean -C KVM;
	$(Q)$(MAKE) clean -C SOL;

include $(PRJ_PATH)/PKConfig/Lx_Script/Makefile.lib

SDK_FEATURE_NAME = JavaAP
SDK_FILE_CP_LIST =  SOL/*.pack.gz KVM/*.pack.gz

include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk
