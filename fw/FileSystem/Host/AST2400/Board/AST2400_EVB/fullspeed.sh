#!/bin/sh 

check_boardid()
{
    retval=0
    # Note: use lowercase against board id
    case "$1" in
        "843") retval=1;; # X10DRG-H(T)
        "852") retval=1;; # X10DRG-Q
        "84b") retval=1;; # X10SRG-F
        "824") retval=1;; # X10DRT-P(T)(IBF)
        "844") retval=1;; # X10DRU-i+
        "854") retval=1;; # X10DRU-X
        *) ;;
    esac
    #if [ $1 = "843" ]; then
    #    retval=1
    #fi

    return $retval
}

if [ "$1" != "y" ] && [ "$1" != "n" ]; then
    exit 1
fi

if [ -f /nv/platform.conf ]; then
    BOARDID=`awk '{print $1;}' /nv/platform.conf`
    if [ $? -eq 0 ]; then
        check_boardid $BOARDID
        if [ $? -eq 1 ]; then
            TMP=`/bin/fw_printenv fullspeed`
            if [ $? -eq 0 ]; then
                TMP=`echo -n $TMP|awk -F= '{print $2;}'`
                if [ $TMP != $1 ]; then
                    /bin/fw_setenv fullspeed $1
                fi
            else
                /bin/fw_setenv fullspeed $1 
            fi
        fi
    fi
fi
