



static char rcsid[] = "$Id: radtest.c,v 1.3.4.3 2004/08/27 21:55:03 flovergine Exp $ Copyright (C) 1999-2004 Francesco P. Lovergine";


#include "yard.h"

void log_err(char * fmt, ...){} 
void log_debug(char * fmt, ...){}
void debug(char * fmt, ...){}


int			fd;
struct sockaddr_in	addr;
struct hostent *	hostent;
int			secret_len;
char *			progname;

u_char req_id;

char r_buf[4096];
char s_buf[4096];
int  u_name_len;
int  u_passwd_len;

int	debug_flag = 0;
int	debug_mem  = 0;
char	*radius_dir = ".";
char	*radius_log = "/dev/tty";
UINT4	now = 0;

void print_buf(void)
{
	int i;
	for (i=0; i< 100; i++)
	{
		printf("%x ", (unsigned char) r_buf[i]);
	}
}


unsigned char RADIUSAuthClient(char* host_name, int radius_port, char* secret, char* u_name, char* u_passwd, char* permissions)
{
	static AUTH_HDR		*ah;
	static AUTH_REQ		*authreq;
	static VALUE_PAIR	*pair;
	static char		*called_id;
	static char		*calling_id;
	static char		argnum;
	static char		argval;
	static fd_set		fdset;
	static int		acct_flag;
	static int		count;
	static int		frame_flag;
	static int		host;
	static int		i;
	static int		len;
	static int		rc;
	static int		sa_len;
	static int		service_type;
	static int		val;
	static int		verbose_flag;
	static struct		sockaddr_in sa_ihd;
	static struct		timeval tv;
	static struct servent *	svp;
	static u_char		*cp;
	static u_char		alen;
	static u_char		id;
	static u_short          lport;

	static char passwd[AUTH_PASS_LEN];
	static char md5_buf[1024];

	acct_flag = 0;
	count = 1;
	frame_flag = 0;
	id = 0;
	service_type = 0;	
	verbose_flag = 0;
	radius_dir = RADIUS_DIR;
	called_id = NULL;
	calling_id = NULL;



	secret_len = strlen(secret);

	if (radius_port) {
		lport = htons(radius_port);
	} else {
		if (acct_flag) {
			svp = getservbyname ("radacct", "udp");
			if (svp != (struct servent *) 0) {
				lport = (u_short) svp->s_port;
			} else {
				lport = htons(ntohs(PW_AUTH_UDP_PORT));
			}
		} else {
			svp = getservbyname ("radius", "udp");
			if (svp != (struct servent *) 0) {
				lport = (u_short) svp->s_port;
			} else {
				lport = htons(ntohs(PW_ACCT_UDP_PORT));
			}
		}
	}

#if 0
	if ((hostent = gethostbyname(host_name))
					== (struct hostent *)NULL) {
		fprintf(stderr, "gethostbyname<%s> error<%d>\n",
				host_name, errno);
		exit(1);
	}

	memcpy( &addr.sin_addr.s_addr,
		hostent->h_addr,
		hostent->h_length);

	host = ntohl(addr.sin_addr.s_addr);

#else
  	addr.sin_addr.s_addr = inet_addr(host_name);
  	host = inet_addr(host_name);
#endif

	addr.sin_family = AF_INET;
	addr.sin_port = lport;


	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		return 0;
	}




	ah = (AUTH_HDR *)s_buf;
	memset(ah, 0, sizeof(*ah));
	if (acct_flag) {
		ah->code = PW_ACCOUNTING_REQUEST;
	} else {
		ah->code = PW_AUTHENTICATION_REQUEST;
	}
	ah->id = id;
	len = AUTH_HDR_LEN;
	u_name_len = strlen(u_name);
	u_passwd_len = strlen(u_passwd);


	cp = ah->data;
	*cp++ = PW_USER_NAME;
	*cp++ = u_name_len + 2;
	memcpy(cp, u_name, u_name_len);
	cp += u_name_len;
	len += u_name_len + 2;


	if (passwd && service_type != PW_CALL_CHECK_USER ) {
		*cp++ = PW_PASSWORD;
		*cp++ = AUTH_PASS_LEN + 2;
		if (u_passwd_len > AUTH_PASS_LEN) {
			u_passwd_len = AUTH_PASS_LEN;
		}

		memset(passwd, 0, AUTH_PASS_LEN);
		memcpy(passwd, u_passwd, u_passwd_len);
		strncpy(md5_buf, secret, sizeof(md5_buf)-1);
		md5_buf[sizeof(md5_buf)-1]='\0';
		memcpy(md5_buf + secret_len, ah->vector, AUTH_VECTOR_LEN);
		md5_calc(cp, md5_buf, secret_len + AUTH_VECTOR_LEN);
		for (i = 0; i < AUTH_PASS_LEN; i++) {
			*cp++ ^= passwd[i];
		}
		len += AUTH_PASS_LEN + 2;
	}


	alen = 4;
	*cp++ = PW_CLIENT_ID;
	*cp++ = alen + 2;
	val = htonl(0x7f000001);	
	memcpy(cp, &val, alen);
	cp += alen;
	len += alen + 2;


	alen = 4;
	*cp++ = PW_CLIENT_PORT_ID;
	*cp++ = alen + 2;
	val = htonl(1);
	memcpy(cp, &val, alen);
	cp += alen;
	len += alen + 2;


	if (service_type) {
		alen = 4;
		*cp++ = PW_USER_SERVICE_TYPE;
		*cp++ = alen + 2;
		val = htonl(service_type);
		memcpy(cp, &val, alen);
		cp += alen;
		len += alen + 2;

	} else if (frame_flag) {
		alen = 4;
		*cp++ = PW_USER_SERVICE_TYPE;
		*cp++ = alen + 2;
		val = htonl(PW_FRAMED_USER);
		memcpy(cp, &val, alen);
		cp += alen;
		len += alen + 2;

		alen = 4;
		*cp++ = PW_FRAMED_PROTOCOL;
		*cp++ = alen + 2;
		val = htonl(PW_PPP);
		memcpy(cp, &val, alen);
		cp += alen;
		len += alen + 2;
	}


	if (called_id!= NULL) {
		alen = (u_char)strlen(called_id);
		*cp++ = PW_CALLED;
		*cp++ = alen + 2;
		memcpy(cp, called_id, alen);
		cp += alen;
		len += alen + 2;
	}



	if (calling_id!= NULL) {
		alen = (u_char)strlen(calling_id);
		*cp++ = PW_CALLING;
		*cp++ = alen + 2;
		memcpy(cp, calling_id, alen);
		cp += alen;
		len += alen + 2;
	}

	ah->length = htons(len);

	if (acct_flag) {
	}

	if ((rc = sendto(fd, (char *)ah, len, 0, 
		(struct sockaddr *)&addr, sizeof addr)) < 0) {
		return 0;
	}

	FD_ZERO(&fdset);
	FD_SET(fd, &fdset);
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	if (select(32, &fdset, NULL, NULL, &tv) < 0) {
		return 0;
	}
	if (FD_ISSET(fd, &fdset)) {
		sa_len = sizeof sa_ihd;
		if ((rc = recvfrom(fd, r_buf, sizeof r_buf, 0,
		
			(struct sockaddr *)&sa_ihd, &sa_len)) < 0) {
			perror("recvfrom: ");
			rad_exit(errno);
		}
	} else {
		return 0;
	}

	ah = (AUTH_HDR *)r_buf;
	switch(ah->code) {
	case PW_AUTHENTICATION_ACK:
		break;


	default:
		return 0;
	}
	
	authreq = radrecv(host, ntohs(lport), secret, (u_char*)r_buf, rc);
	
	if (authreq != (AUTH_REQ *)NULL) {
		pair = authreq->request;
		while (pair != (VALUE_PAIR *)NULL) {
			if (0x1A == pair->attribute)
		strcpy(permissions, pair->strvalue);
			pair = pair->next;
		}
		close(fd);
		reqfree(authreq, "radrecv");
		return 1;
	}

	close(fd);
}




AUTH_REQ *
radrecv( UINT4 host, u_short udp_port, char *secret, u_char *buffer,int length )
{
	u_char		*ptr;
	char		*bufalloc();
	AUTH_HDR	*auth;
	int		totallen;
	int		attribute;
	int		attrlen;
	int		vendor;
	int		vsa;
	int		vsattrlen;
	DICT_ATTR	*attr;
	DICT_ATTR	*dict_attrget();
	DICT_ATTR	*dict_vsattrget();
	UINT4		lvalue;
	VALUE_PAIR	*first_pair;
	VALUE_PAIR	*prev;
	VALUE_PAIR	*pair;
	VALUE_PAIR	*pairalloc();
	AUTH_REQ	*authreq;
	AUTH_REQ	*reqalloc();
	void		hexdump();
	void		pairfree();
	void		rad_exit();
	void		reqfree();

	if (length < AUTH_HDR_LEN) {            
                log_err("radrecv: runt packet of %d bytes from %s/%d\n",
			length, ipaddr2strp(host), udp_port);
                return ((AUTH_REQ *)NULL);
        }



	authreq = reqalloc("radrecv");

	auth = (AUTH_HDR *)buffer;
	totallen = ntohs(auth->length);
	if (totallen > length) {	
		log_err("radrecv: message from %s/%d claimed length %d, only %d bytes received\n", ipaddr2strp(host), udp_port, totallen, length);
		reqfree(authreq,"radrecv");
		return((AUTH_REQ *)NULL);
	}

	debug("message received from %s/%d.%d code=%d, length=%d\n",
		ipaddr2strp(host), udp_port, auth->id, auth->code, totallen);

	if (debug_flag > 1) {
		hexdump(buffer,totallen);
	}

	authreq->ipaddr = host;
	authreq->udp_port = udp_port;
	authreq->id = auth->id;
	authreq->code = auth->code;
	memcpy(authreq->vector, auth->vector, AUTH_VECTOR_LEN);
	strncpy(authreq->secret,secret,20);
	authreq->secret[19]='\0';


	ptr = auth->data;
	length = totallen - AUTH_HDR_LEN;
	first_pair = (VALUE_PAIR *)NULL;
	prev = (VALUE_PAIR *)NULL;

	while(length > 0) {

		attribute = *ptr++;
		attrlen = *ptr++;
		if(attrlen < 2) {
			length = 0;
			continue;
		}
		attrlen -= 2;
		if ( attrlen > AUTH_STRING_LEN ) {
			log_err("radrecv: attribute %d from %s too long, length of %d > %d\n",
				attribute, req2strp(authreq), attrlen, AUTH_STRING_LEN);
			reqfree(authreq,"radrecv");
			return((AUTH_REQ *)NULL);
		}
		pair = pairalloc("radrecv");


		switch(attribute) {
			case (0x1a):
				pair->attribute = attribute;
				pair->type = PW_TYPE_STRING;
				sprintf(pair->name,"Vendor-Specific");
				break;
			default:
				snprintf(pair->name,VALUE_PAIR_NAME_LEN,"Unknown-%d",attribute);
				pair->attribute = attribute;
				pair->type = PW_TYPE_STRING;
		}

		if (pair->attribute == PW_VENDOR) {	
			if (attrlen < 6 || 
			    ((vsattrlen = *(ptr+5)) != (attrlen-4))) {
				pair->vendor = 0;
				pair->vsattribute = 0;
				pair->type = PW_TYPE_STRING;
			} else {
				memcpy(&vendor, ptr, sizeof(UINT4));
				vendor = ntohl(vendor);
				ptr += 4;
				vsa = *ptr++;
				attrlen = vsattrlen - 2;
				ptr++;
				length -= 6;
				pair->vendor = vendor;
				pair->vsattribute = vsa;
				if((attr = dict_vsattrget(vendor,vsa)) != (DICT_ATTR *)NULL) {
					strncpy(pair->name, attr->name, VALUE_PAIR_NAME_LEN-1 );
					pair->name[VALUE_PAIR_NAME_LEN-1]='\0';
					pair->type = attr->type;
				} else {
					snprintf(pair->name,VALUE_PAIR_NAME_LEN,"Vendor-Specific-%d-%d",vendor,vsa);
					pair->type = PW_TYPE_STRING;
				}
			}
		}

		switch(pair->type) {

		case PW_TYPE_STRING:
#if defined(ASCEND_BINARY)
		case PW_TYPE_ABINARY:
#endif
			memcpy(pair->strvalue, ptr, attrlen);
			pair->strvalue[attrlen] = '\0';
			pair->lvalue = attrlen;
			if(first_pair == (VALUE_PAIR *)NULL) {
				first_pair = pair;
			}
			else {
				prev->next = pair;
			}
			prev = pair;
			break;

		case PW_TYPE_INTEGER:
		case PW_TYPE_IPADDR:
		case PW_TYPE_DATE:
			memcpy(&lvalue, ptr, sizeof(UINT4));
			pair->lvalue = ntohl(lvalue);
			if(first_pair == (VALUE_PAIR *)NULL) {
				first_pair = pair;
			}
			else {
				prev->next = pair;
			}
			prev = pair;
			break;

		default:
			debug("    %s (Unknown Type %d)\n",
				attr->name,attr->type);
			pairfree(pair,"radrecv");
			break;
		}
		ptr += attrlen;
		length -= attrlen + 2;
	}
	authreq->request = first_pair;

	authreq->timestamp = now;	

	authreq->packet = bufalloc(totallen,"radrecv");
	memcpy(authreq->packet,buffer,totallen);

	return(authreq);
}

void
usage(void)
{
	printf("usage: %s -d called_id -f -g calling_id -h -i id -p port -s secret -t type -v -x -u username password\n", progname);
	exit(0);
}

void
rad_exit(int rc)
{
	exit(rc);
}

void
version(void)
{
	printf("%s $Date: 2004/08/27 21:55:03 $\n", progname);
	exit(0);
}
