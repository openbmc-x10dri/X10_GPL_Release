-include $(PRJ_PATH)/.config
-include $(PRJ_PATH)/.machine
include $(PRJ_PATH)/PKConfig/Lx_Script/Makefile.lib
WEB_PATH = $(PRJ_PATH)/Web_Server
export WEB_PATH

all:
	$(Q)$(ECHO_CMD) "******************** build web server ********************"
	$(Q)make -C OS/Linux/
	
install:
#copy WEB pages/CGI/Java
	$(Q)$(ECHO_CMD) "******************** install web server ********************"
	$(Q)if [ ! -d $(WEBFS_PATH) ];then mkdir -p $(WEBFS_PATH);fi
	make install --directory=$(WEB_PATH)/OS/Linux/Web_Style/$(WEBSTYLE-y)
	
clean:
	$(Q)make -C OS/Linux/ clean

clean_all: clean

clean_ipmi_cgi:
	$(Q)rm -f `find . -name *.o`; rm -f `find . -name *.d`; rm -f `find . -name *.cgi`;


SDK_FEATURE_NAME = Web_Server

PATTERN = '*.c' '*.h' '*.in' 'Makefile' '*.js' '*.css' '*.www' '*.htm' '*.html' \
 '*.png' '*.gif' '*.bmp' '*.jnlp' '*.ico' '*.jpg' '*.tar.gz'
FILE_LIST = $(call GEN_SEARCH_LIST,$(PATTERN),$(foreach n,$(WEBSTYLE),OS/Linux/Web_Style/$(n)/),,)


FILE_LIST +=$(wildcard ./Makefile \
./httpd/httpd \
./httpd/*.tar.gz \
./httpd/*.conf \
./httpd/*.pem \
./httpd/Makefile \
./OS/Linux/*.c \
./OS/Linux/Makefile \
./OS/Linux/inc/*.h \
./OS/Linux/lib/*.c \
./OS/Linux/OEM/$(MYMCU)/Board/$(BOARD)/*.c \
./OS/Linux/lib/Makefile)

ifeq ($(CONFIG_EXTRACT_ALL_OBJ),y)
SDK_FILE_CP_LIST = $(FILE_LIST:.c=.o)
else
SDK_FILE_CP_LIST = $(FILE_LIST)
endif
include $(PRJ_PATH)/PKConfig/Lx_Script/Extract.mk

