#!/bin/bash

#BL_SUPERMICRO_X7SB3_2012-04-26_B0070

ConFile_Path=$(pwd)/FileSystem/Host/HERMON/Board/SuperMicro_X7SB3
ConFiles=`find $ConFile_Path -name 'platform_*.xml' |xargs ls`

echo "please input TagName:"
read tagname
echo "please input version"
read version
ver1=`echo $version| awk  'BEGIN {FS="."} {print $1}'`
ver2=`echo $version| awk  'BEGIN {FS="."} {print $2}'`

for i in $ConFiles
do
    mv $i $i.old
    echo "Modify file ${i##/*/}  ...."
    cat  $i.old |  sed -e "s/BL_[A-Z0-9].*_[0-9]\{4\}-[0-1][0-9]-[0-3][0-9]_B[0-9]*/$tagname/" > $i
    mv $i $i.old
    echo "Modify firmware version ....."
    cat  $i.old |  sed -e "s/FirmwareRev1=\"0x[0-9]*\"/FirmwareRev1=\"0x$ver1\"/" | sed -e "s/FirmwareRev2=\"0x[0-9]*\"/FirmwareRev2=\"0x$ver2\"/" > $i
    rm $i.old 
done
