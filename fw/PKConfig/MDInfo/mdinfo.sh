#!/bin/bash

ConFile_Path=$2
echo $ConFile_Path
FWv1=`cat $ConFile_Path/conf/version.xml |awk '/FirmwareRev/ {print $4}'|cut -d x -f2 |sed "s/\"//"`
FWv2=`cat $ConFile_Path/conf/version.xml |awk '/FirmwareRev/ {print $5}'|cut -d x -f2 |sed "s/\"//"`

echo "Firmware revision is $FWv1.$FWv2"
if [ "$1" == "2" ]; then
cd ../PKConfig/MDInfo/;./mdinfo -c 1 -v $FWv1 -m $FWv2 -f ../../images/AST2400_all.bin
fi
mv *.bin ../../images
