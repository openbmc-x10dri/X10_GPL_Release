-include $(PRJ_PATH)/.SDKPath
-include $(PRJ_PATH)/.config
-include $(PRJ_PATH)/.machine
include $(PRJ_PATH)/PKConfig/Lx_Script/Makefile.lib

all: reload_cgi

reload_cgi:
	@echo "*** COPY CGIs"
	@cp -af ./CGIs/*.cgi .

CLEAN_PATTERN = '*.o' '*.d'
CLEAN_FILES = $(call GEN_SEARCH_LIST,$(CLEAN_PATTERN),./,,)
include $(PRJ_PATH)/PKConfig/Lx_Script/clean.mk

clean_all: clean

extract:
	@echo "******************** extract web data ********************"
