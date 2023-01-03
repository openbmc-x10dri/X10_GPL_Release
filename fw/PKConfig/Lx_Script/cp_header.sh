#!/bin/bash

files=`find ./ -name "*.h"`

for i in $files ;do
	file_path=$1/`dirname $i`
	if [ ! -d $file_path ];then
		mkdir -p $file_path
	fi
	cp $i $file_path
done
