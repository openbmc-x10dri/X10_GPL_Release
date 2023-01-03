CLEANOBJS = $(sort $(OBJS) $(OBJS:.o=.d) $(LIBOBJS) $(LIBOBJS:.o=.d))
EXCLUDEOBJW = $(strip $(subst ", ,$(CONFIG_EXCLUDE_OBJS)))

ifeq ($(CONFIG_EXTRACT_MOD),y)
#    LIBOBJS = $(foreach f,$(LIBOBJS),$(if  $(filter-out  $(EXCLUDEOBJS),$(notdir $(f))),$(f)))
endif

ifneq ($(strip $(LIBOBJS)),)
lib:$(LIBOBJS)
ifeq ($(LIBNAME),)
	@echo "the library name (LIBNAME) is not assigned!"
	@/bin/false
else
	$(Q)$(AR) $(ARFLAGS) $(LIBPATH)/liblxall.a  $(LIBOBJS)
    ifeq ($(strip $(BUILD_OPTION)),0)
	@echo " AR "$(LIBNAME)
	$(Q)$(AR) $(ARFLAGS) $(LIBPATH)/$(LIBNAME) $(LIBOBJS)
    else
	@echo " AR "$(LIBNAME)
	$(Q)$(AR) $(ARFLAGS) $(LIBPATH)/$(LIBNAME) $(LIBOBJS) >>/dev/null 2>&1
#	$(Q)$(CC)  -Wl -shared   -o $(LIBPATH)/$(LIBNAME:.a=.so) $(LIBOBJS)
    endif
    ifeq ($(CONFIG_EXTRACT_MOD),y)
	@for i in $(EXCLUDEOBJW); do for j in $(LIBOBJS); do /bin/bash $(PRJ_PATH)/PKConfig/Lx_Script/ExtractLibHeader.sh $$i $$j $(PRJ_PATH);  done; done
    endif
endif
else 
.PHONY: lib
lib:
	@:
endif
clean:
	@echo CLEAN $(notdir $(CLEANOBJS)) 
	@for i in $(CLEANOBJS); do if [ -f $$i ];then rm $$i ;fi ; done
%.o:%.c
	@echo " CC "$(notdir $@)
	$(call check_depreciated_function,$<)
	$(Q)$(CC) $(CFLAGS) -c $< -o $@ 
%.d:%.c
	@$(CC) -M $(CFLAGS) $< > $@.$$$$;\
	sed 's,\($*\).o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -f   $@.$$$$
-include $(sort  $(LIBOBJS:.o=.d) $(OBJS:.o=.d))
