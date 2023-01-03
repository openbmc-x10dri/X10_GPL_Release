#!/bin/sh 

TMP=`/bin/fw_printenv verify`
if [ $? -eq 0 ]; then
	TMP=`echo -n $TMP|awk -F= '{print $2;}'`
	if [ $TMP = "n" ]; then
		/bin/fw_setenv verify y
	fi
fi
