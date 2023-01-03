#!/bin/bash

#KERNEL_START_ADDR_DEC=$(($((16#$FLASH_BASE_ADDR_VALUE))+$((16#$KERNEL_OFFSET_VALUE))))
#KERNEL_START_ADDR_HEX=$(echo "obase=16;ibase=10; $KERNEL_START_ADDR_DEC"|bc)
echo "KERNEL_START_ADDR: " $KERNEL_START_ADDR
./mkimage -A arm -O linux -T kernel -C gzip -a 40008000 -e 40008000 -n $KERNEL_START_ADDR -d kernel.bin out_kernel.bin
mv rootfs out_rootfs_img.bin
mv webfs out_webfs_img.bin
./mk_uboot_env_img 
if [ $? -ne 0 ];then exit 1;fi
./mkbin AST2400_all.bin
if [ $? -ne 0 ];then exit 1;fi
rm kernel.bin