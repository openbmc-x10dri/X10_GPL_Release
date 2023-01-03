#!/bin/bash


var=`sed -n '/cgi.assign\s*=\s*(/,/)/p' $1 |grep sh`
if [ ! -z "$var" ];then exit -1 ;fi

var=`sed -n '/cgi.assign\s*=\s*(/,/)/p' $1 |grep ash`
if [ ! -z "$var" ];then exit -1 ;fi

var=`sed -n '/server.modules\s*=\s*(/,/)/{/^#.*mod_alias/p}' $1`
if [ -z "$var" ];then exit -1 ;fi

var=`grep -s "#dir-listing.activate" $1`
if [ -z "$var" ];then exit -1 ;fi

