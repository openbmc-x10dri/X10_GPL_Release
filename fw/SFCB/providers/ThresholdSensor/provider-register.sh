#!/bin/sh
# $Id: provider-register.sh,v 1.13 2006/02/09 13:40:10 mihajlov Exp $
# ==================================================================
# (C) Copyright IBM Corp. 2005
#
# THIS FILE IS PROVIDED UNDER THE TERMS OF THE COMMON PUBLIC LICENSE
# ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
# CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
#
# You can obtain a current copy of the Common Public License from
# http://www.opensource.org/licenses/cpl1.0.php
#
# Author:       Viktor Mihajlovski <mihajlov@de.ibm.com>
# Contributors:
# Description:  Script to install class definitions (MOFs) and 
#               registration data for a variety of supported CIMOMs
# ==================================================================



sfcb_transform()
{
    OUTFILE=$1
    shift
    regfiles=$*

#produce sfcb registraion
    for rf in $regfiles
    do
      cat $rf | grep -v '^[[:space:]]*#.*' | while read CLASSNAME NAMESPACE PROVIDERNAME PROVIDERMODULE CAPS
      do
	chatter "Registering class" $CLASSNAME
	cat >> $OUTFILE <<EOFC
[$CLASSNAME]   
   provider: $PROVIDERNAME
   location: $PROVIDERMODULE
   type: $CAPS
   namespace: $NAMESPACE
#
EOFC
      done
    done
}

sfcb_rebuild()
{
  
	chatter "Rebuilding repository."
	sfcbrepos -f $endian -s $stagedir -r $regdir -c $cimdir
	if test $? != 0
	then
	    echo "Repository rebuild failed." >&2
	    return 1
	fi
	
}

sfcb_install()
{    
    mymofs=
    mregs=
    mofmode=1
    while test x$1 != x
    do 
      if test $1 = ":"
      then 
	  mofmode=0
	  shift
	  baseregname=`basename $1 .registration`
	  continue
      fi
      if test $mofmode = 1
      then
	  mymofs="$mymofs $1"
      else
	  myregs="$myregs $1"
      fi
      shift
    done

    for _TEMPDIR in /var/tmp /tmp
    do
      if test -w $_TEMPDIR
      then
	  _REGFILENAME=$_TEMPDIR/$baseregname.reg
	  break
      fi
    done

    trap "rm -f $_REGFILENAME" EXIT


    if sfcb_transform $_REGFILENAME $myregs
    then
	chatter "Staging provider registration."
	sfcbstage -r $_REGFILENAME $mymofs -s $stagedir
	if test $? != 0 
	then
	    echo "Failed to stage provider registration." >&2
	    return 1
	fi
	sfcb_rebuild
    else
	echo "Failed to build sfcb registration file." >&2
	return 1
    fi
}

sfcb_uninstall()
{    
    mymofs=
    while test x$1 != x
    do 
      if test $1 = ":"
      then 
	  shift
	  baseregname=`basename $1 .registration`
	  break
      fi
      mymofs="$mymofs `basename $1`"
      shift
    done
    
    # "Unstage" MOFs and the registration file
    chatter "Unstaging provider registrations."
    sfcbunstage -r $baseregname.reg $mymofs

    # Rebuild repository
    sfcb_rebuild
}


cim_server()
{
    for exname in sfcbd cimserver owcimomd
    do
      if pegasus_path $exname > /dev/null
      then
	  case $exname in
	      sfcbd) echo sfcb; return 0;;
	  esac
	  break;
      fi
    done
    echo unknown
    return 1
}

usage() 
{
    echo "usage: $0 [-h] [-v] [-d] [-t <cimserver>] -r regfile ... -m mof ..."
}

chatter()
{
    if test x$verbose != x
    then
	echo $*
    fi
}

gb_getopt()
{
    rmode=0
    mmode=0
    options=
    moffiles=
    registrations=
    while [ -n "$1" ]
    do
      case $1 in
	  -r) mmode=0;
	      rmode=1;
	      shift;;
	  -m) mmode=1;
	      rmode=0;
	      shift;;
	  -*) mmode=0;
	      rmode=0;
	      options="$options $1";
	      shift;;
	  **) if [ $mmode = 1 ] 
	      then moffiles="$moffiles $1"       
	      elif [ $rmode = 1 ]
	      then registrations="$registrations -r $1" 
	      else options="$options $1";
	      fi; 
	      shift;;
      esac
    done
    echo $options $registrations $moffiles 
}
prepargs=`gb_getopt $*`
args=`getopt dvhX:t:r:s:c:i: $prepargs`
rc=$?

if [ $rc = 127 ]
then
    echo "warning: getopt not found ...continue without syntax check"
    args=$prepargs
elif [ $rc != 0 ]
then
    usage $0
    exit 1
fi

set -- $args


while [ -n "$1" ]
do
  case $1 in
      -h) help=1; 
	  shift;
	  break;;
	  -s) stagedir="$2"
	  shift 2;;
	  -i) regdir="$2"
	  shift 2;;
	  -c) cimdir="$2"
	  shift 2;;
      -v) verbose=1; 
	  shift;;
      -X) endian="-X $2"; 
	  shift 2;;
      -d) deregister=1; 
	  shift;;
      -t) cimserver=$2;
	  shift 2;;
	  
      -r) regs="$regs $2";
	  shift 2;;
      --) shift;
	  break;;
      **) break;;
  esac
done

mofs=$*

if [ "$help" = "1" ]
then
    usage
    echo -e "\t-h display help message"
    echo -e "\t-v verbose mode"
    echo -e "\t-d deregister provider and uninstall schema"
    echo -e "\t-t specify cimserver type (sfcb)"
    echo -e "\t-r specify registration files"
    echo -e "\t-m specify schema mof files"
    echo -e "\t-X create repository for alternate platform (sfcb only at the moment)."
    echo
    echo Use this command to install schema mofs and register providers.
    echo CIM Server Type is required as well as at least one registration file and one mof.
    exit 0
fi

if test x"$mofs" = x || test x"$regs" = x
then
    usage $0
    exit 1
fi

if test x$cimserver = x
then
    cimserver=`cim_server`
    if test $? = 0
    then
	chatter "Autoselected CIM server type:" $cimserver
    else
	echo "CIM server type could not be determined, specify with -t." >&2
	exit 1
    fi
fi
if test x$deregister = x
then
    case $cimserver in
	sfcb)    sfcb_install $mofs ":" $regs;;
	**)	echo "Invalid CIM Server Type " $cimserver && exit 1;;
    esac
else
    case $cimserver in
	sfcb)    sfcb_uninstall $mofs ":" $regs;;
	**)	echo "Invalid CIM Server Type " $cimserver && exit 1;;
    esac
fi    
