.PHONY: extract_allobj
include $(PRJ_PATH)/.SDKPath
include $(PRJ_PATH)/PKConfig/Lx_Script/Makefile.lib
override BOARD=
extract:
	$(Q)$(ECHO_CMD) "==================== Build firmware (Stage 1) ===================== "
	$(Q)make -f $(PRJ_PATH)/Makefile
	$(Q)$(ECHO_CMD) "==================== Build firmware (Stage 2) ===================== "
	$(Q)make install -f $(PRJ_PATH)/Makefile
	$(Q)$(ECHO_CMD) "==================== Finish Building firmware ===================== "
	$(Q)$(ECHO_CMD) "=================== Extract all objects ====================="
	$(Q)make extract_basic -f $(PRJ_PATH)/PKConfig/Lx_Script/ExtractRootBasic.mk
	$(Q)$(CP_CMD) -af .config $(SDKPATH)/.config
	$(Q)$(call SED_TASK,'/EXTRACT\|Extract/d',$(SDKPATH)/.config)
	$(Q)$(call SED_TASK,'/RADIUS-y/d',$(SDKPATH)/Makefile)
	$(Q)$(CP_CMD) -af ./autoconfig.h $(SDKPATH)/autoconfig.h
	$(Q)$(call SED_TASK,'/CONFIG_EXTRACT\|CONFIG_EXCLUDE/d',$(SDKPATH)/autoconfig.h)
	$(Q)$(CP_CMD) -f $(SDKPATH)/.config $(SDKPATH)/.config.default
	$(Q)$(CP_CMD) -f $(SDKPATH)/autoconfig.h $(SDKPATH)/autoconfig.h.default
	$(Q)rm -rf ./$(SDKPATH)/*.in
	$(Q)$(CP_CMD) ./PKConfig/Lx_Script/Buildcmd/*.sh $(SDKPATH)/