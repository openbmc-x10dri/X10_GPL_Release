include $(PRJ_PATH)/.config

all:copy_ipmi_bin_lib

.PHONY: extract

copy_ipmi_bin_lib:
	@echo "*** COPY binaries and libraries"
	@if [ -d $(BINPATH) ]; then cp -af ./bin/* $(BINPATH)/; fi
	@if [ -d $(LIBPATH) ]; then cp -af ./lib/* $(LIBPATH)/; fi

install:


extract:
	@echo "************************ extract IPMI ************************"

clean:
	$(Q)echo "clean IPMI"


