#!/bin/sh

#!/bin/sh -e

prefix=/wsman/openwsman

CERTFILE=${prefix}/etc/openwsman/servercert.pem
KEYFILE=${prefix}/etc/openwsman/serverkey.pem
CNFFILE=${prefix}/etc/openwsman/ssleay.cnf

if [ "$1" != "--force" -a -f $KEYFILE ]; then
  echo "$KEYFILE exists!  Use \"$0 --force.\""
  exit 0
fi

if [ "$1" = "--force" ]; then
  shift
fi

echo
echo creating selfsingned certificate
echo "replace it with one signed by a certification authority (CA)"
echo
echo enter your ServerName at the Common Name prompt
echo

# use special .cnf, because with normal one no valid selfsigned
# certificate is created

export RANDFILE=/dev/random
/wsman/wsman/openssl/local/bin/openssl req -days 365 $@ -config $CNFFILE \
  -new -x509 -nodes -out $CERTFILE \
  -keyout $KEYFILE
chmod 600 $KEYFILE

