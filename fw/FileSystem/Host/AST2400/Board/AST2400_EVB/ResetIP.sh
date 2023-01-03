#kill process
killall -10 ikvmserver
killall -15 usb
killall -9 uima
killall -9 uiso
sleep 1

#remove driver
/sbin/rmmod usb_hid.ko
while [ $? != 0 ]
do
	sleep 1;
	/sbin/rmmod usb_hid.ko
done

/sbin/rmmod ikvm_vmass.ko
while [ $? != 0 ]
do
	sleep 1;
	/sbin/rmmod ikvm_vmass.ko
done
sleep 1

#insert driver
/sbin/insmod /bin/module/ikvm_vmass.ko
/sbin/insmod /bin/module/usb_hid.ko
sleep 1

#re-init process
/bin/usb&
/bin/uima&
/bin/uiso&
/bin/ikvmserver&
