#!/bin/bash
function RM_CMD()
{
	if [ -d $1 ] || [ -f $1 ];then rm -rf $1 && echo "Delete " $1;fi
}


RM_CMD busybox/busybox  
RM_CMD busybox/busybox.log 
RM_CMD DDNS/tools/bind-9.3.2-P2 
RM_CMD DHCPV6/wide-dhcpv6 
RM_CMD FileSystem/Host/HERMON/tmp 
RM_CMD FileSystem/Host/HERMON/tmp_fs 
RM_CMD FileSystem/Host/HERMON/web_fs 
RM_CMD FileSystem/rootfs 
RM_CMD FileSystem/rootfs_tmp 
RM_CMD FileSystem/webfs 
RM_CMD FileSystem/webfs_tmp 
RM_CMD IKVM/IKVMServer/build 
RM_CMD IKVM/ServerLib/build
RM_CMD IKVM/ServerLib/dist
RM_CMD IKVM/Driver/Video/OS/Linux/Host/HERMON/Modules.symvers  
RM_CMD IKVM/IKVMServer/dist 
RM_CMD JavaAP/KVM/iKVM__V1.57.8.0x0.jar
RM_CMD JavaAP/KVM/iKVM__V1.57.8.0x0.jar.pack.gz
RM_CMD Kernel/Host/HERMON/image
RM_CMD Kernel/Host/HERMON/linux
RM_CMD libXML2/libxml2
RM_CMD LLDP/openlldp-0.3alpha
RM_CMD NTP/bin/ntp_setenv.o
RM_CMD NTP/tools/ntp-4.2.4p4
RM_CMD OpenLDAP/openldap
RM_CMD OpenSSL/openssl
RM_CMD OpenWSMAN/openwsman
RM_CMD SFCB/sblim-sfcb-1.3.2
RM_CMD SFCB/zlib-1.2.3
RM_CMD SFCB/SFCB
RM_CMD SFCB/SFCBx86
RM_CMD SFCC/curl
RM_CMD SFCC/sfcc
RM_CMD SMASH/dropbear
RM_CMD SMASH/dropbear-0.52
RM_CMD SMASH/dropbear_patch
RM_CMD SMASH/SFCC_API/SFCC_API.o
RM_CMD SMASH/SFCC_API/show.o
RM_CMD SMASH/shell/flex-2.5.35
RM_CMD SMASH/shell/readline-5.2
RM_CMD SMASH/shell/shell
RM_CMD SMASH/shell/termcap-1.3.1
RM_CMD SMASH/SMASH
RM_CMD SMASH/tree-1.5.2.2-src
RM_CMD SMTP/libgsasl-1.4.4
RM_CMD SMTP/libgsasl-1.4.4.tar.gz
RM_CMD SMTP/libgsasl_tmp
RM_CMD SMTP/libntlm-1.2
RM_CMD SMTP/libntlm-1.2.tar.gz
RM_CMD SMTP/libntlm_tmp
RM_CMD SMTP/State_Machine
RM_CMD SMTP/smtp
RM_CMD SNMP/ipmiAgentPluginObject.o
RM_CMD SNMP/ipmiAgentPluginObject.so
RM_CMD SNMP/net-snmp-5.4.2.1
RM_CMD SNMP/SNMP_BIN
RM_CMD SNMP/snmpd.log
RM_CMD UPNP/Device/Host/HERMON/Board/SuperMicro_X7SB3/IPMI_device/sample_util.o
RM_CMD UPNP/Device/Host/HERMON/Board/SuperMicro_X7SB3/IPMI_device/upnp_IPMI_Console.o
RM_CMD UPNP/Device/Host/HERMON/Board/SuperMicro_X7SB3/IPMI_device/upnp_IPMI_device.o
RM_CMD UPNP/libupnp-1.3.1
RM_CMD ToolChain/Host/HERMON/gcc-3.4.4-glibc-2.3.5-armv4
RM_CMD ToolChain/Host/i386/mingw32
RM_CMD ToolChain/Host/x86_64/mingw-w64
RM_CMD Web_Server/httpd/lighttpd
RM_CMD images
RM_CMD bin
RM_CMD NW_FIREWALL/iptables-1.4.9.1
RM_CMD NW_FIREWALL/tmp
RM_CMD JavaAP/jdk1.6.0_14
RM_CMD JavaAP/apache-ant-1.7.1

find ./ -name "*.symvers" |xargs rm -rf
find ./ -name "*.*~" |xargs rm -rf
find ./ -name "*.o" | xargs rm -rf
find ./ -name ".metadata" |xargs rm -rf
find ./ -name "*.*.bak" |xargs rm -rf
find ./ -name "*.bak" |xargs rm -rf
find ./ -name "*.d" |xargs rm -rf
find ./ -name "*.mod.c" |xargs rm -rf
find ./ -name "*.ko" |xargs rm -rf
find SFCB/ -name "*.so" |xargs rm -rf
find SFCB/ -name "*.so.*" |xargs rm -rf
find Web_Server/ -name "*.cgi" |xargs rm -rf


