
KBUILD_NOPEDANTIC=1
export KBUILD_NOPEDANTIC
override LDFLAGS=
default:
	$(Q)echo $(PWD)
	$(Q)if [ ! -z "$(wildcard *.c)" ];then $(MAKE) -j -C $(KERNELDIR) M=$(PWD) modules;fi
	$(Q)if [ -d ${MODULEPATH} ];then cp $(obj-m:.o=.ko) ${MODULEPATH}; fi
