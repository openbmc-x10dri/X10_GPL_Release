#ifndef __YARD_H
#define __YARD_H







#include	<config.h>

#ifdef IPASS
#define USE_SSL
#endif

#ifdef HAVE_SYS_TYPES_H
#include        <sys/types.h>
#endif
#include        <sys/socket.h>

#ifdef HAVE_SYS_FILE_H
#include        <sys/file.h>
#endif
#include        <sys/ipc.h>
#include        <netinet/in.h>
#ifdef HAVE_SYS_STAT_H
#include	<sys/stat.h>
#endif
#include        <stdlib.h>
#include        <stdio.h>
#include        <netdb.h>

#ifdef TIME_WITH_SYS_TIME
# include        <sys/time.h>
# include        <time.h>
#else
# ifdef HAVE_SYS_TIME_H
#   include 	<sys/time.h>
# else
#   include     <time.h>
# endif
#endif

#include        <ctype.h>
#include        <pwd.h>
#include	<grp.h>
#ifdef HAVE_SYSLOG_H
#include        <syslog.h>
#endif
#include        <signal.h>
#include        <errno.h>
#ifdef	HAVE_FCNTL_H
#include        <fcntl.h>
#endif
#ifdef HAVE_UNISTD_H
#include        <unistd.h>
#endif
#ifdef 	HAVE_SYS_WAIT_H
#include        <sys/wait.h>
#endif
#ifdef	HAVE_LIMITS_H
#include        <limits.h>
#endif
#include        <stdarg.h>
#ifdef 	HAVE_SHADOW_H
#include 	<shadow.h>
#endif
#ifdef	HAVE_SECURITY_PAM_APPL_H
#include 	<security/pam_appl.h>
#endif

#if defined(HAVE_STRINGS_H)
#include        <strings.h>
#endif
#if defined(HAVE_STRING_H)
#include        <string.h>
#endif

#if defined(HAVE_MACHINE_ENDIAN_H)
#include	<machine/endian.h>
#endif
#if defined(HAVE_MACHINE_INLINE_H)
#include	<machine/inline.h>
#endif

#if defined(HAVE_SYS_SELECT_H)
#include	<sys/select.h>
#endif




#if !defined(GDBM_SYNC)
#define GDBM_SYNC	0
#endif

#if defined(__alpha)
typedef unsigned int    UINT4;
#else
typedef unsigned long   UINT4;
#endif

#include	"radius.h"
#include	"md5.h"
#include 	"prototypes.h"


#if !defined(USE_PORTABLE_SNPRINTF)

#ifndef HAVE_SNPRINTF
#ifdef HAVE___SNPRINTF
#define HAVE_LOCAL_SNPRINTF
#define snprintf __snprintf
#endif
#else
#define HAVE_LOCAL_SNPRINTF
#endif

#ifndef HAVE_VSNPRINTF
#ifdef HAVE___VSNPRINTF
#define HAVE_LOCAL_SNPRINTF
#define snprintf __vsnprintf
#endif
#else
#define HAVE_LOCAL_SNPRINTF
#endif

#endif



#define RADIUS_HOLD		"holdusers"
#define RADIUS_USER_STATS	"user-stats"
#define RADIUS_LAST             "radlast"
#define RADIUS_DENY             "denyuser"
#define RADIUS_STOP             "stopuser"
#define RADIUS_ALLOW            "allowuser"

#if defined(HAVE_LIBPAM)
#define RADIUS_PAM_SERVICE	"yard"
#endif

#define USERNAME_MAX   32
    
#define P_LOGIN_UNK    -2
#define P_FRAMED_UNK   -1
#define P_UNKNOWN       0
#define P_TELNET        1
#define P_RLOGIN        2
#define P_TCP_CLEAR     3
#define P_PORTMASTER    4
#define P_PPP           5
#define P_SLIP          6
#define P_CSLIP         7


#define	MAX_ACCT_QUEUE	1000 


#define Su_DAY 		0001
#define Mo_DAY 		0002
#define Tu_DAY 		0004
#define We_DAY 		0010
#define Th_DAY 		0020
#define Fr_DAY 		0040
#define Sa_DAY 		0100


#define Wk_DAY   Mo_DAY | Tu_DAY | We_DAY | Th_DAY | Fr_DAY 
#define Al_DAY   Wk_DAY | Sa_DAY | Su_DAY


typedef char STRING[254]; 


typedef struct {
    time_t		time;
    UINT4               nas_ip;
    unsigned int        port_type;
    unsigned int        port_number;
    UINT4               client_ip;
    int                 proto;
} port_entry;

typedef struct {
    unsigned int   	on_line;       
    unsigned long	input_octets;  
    unsigned long	output_octets; 
    unsigned int	nr_logins;     
} today_user_entry;

# define MONTHS         12
# define DAYS_PER_MONTH 31

# define DAY_LIMIT   1
# define MONTH_LIMIT 2
# define YEAR_LIMIT  3

typedef struct {
    unsigned int     logins;        
    today_user_entry day[MONTHS][DAYS_PER_MONTH]; 
} user_entry;

typedef struct {
    char port;
    char proto;
    char port_type;
    char term_cause;
} log_entry;

typedef struct {
    char 	login[USERNAME_MAX]; 
    log_entry 	ent;   		
    UINT4 	nas_ip;        	
    UINT4 	client_ip;     	
    time_t 	ut_time;       	
    time_t 	length;        	
    UINT4 	inb;	       	
    UINT4 	outb;	       	
    UINT4	rxrate;		
    UINT4	txrate;		
    STRING	callingid;	
    STRING	calledid;	
} radlast;

typedef struct acct_packet {
    char 	username[USERNAME_MAX];
    char 	sessionid[11];		
    int 	port;
    UINT4	nas_ip;
    int		type; 
    struct acct_packet	*next;
} acct_packet;			


struct  time_frame {
    short 	t_days;
    short 	t_start;
    short 	t_end;
};


#ifndef	PATH_MAX
#ifdef 	_POSIX_PATH_MAX
#define PATH_MAX _POSIX_PATH_MAX
#else 
#define PATH_MAX 512
#endif 
#endif 

#define ID_LENGTH 32

#if defined(SECURID) || defined(ACTIVCARD)
#define SMARTCARD
#endif

#if defined(__MAIN__)

#if defined(PAM)
int usepamacct=0;
int usepamauth=0;
#endif

#else

#if defined(PAM)
extern int usepamacct;
extern int usepamauth;
#endif

#endif

#endif 

