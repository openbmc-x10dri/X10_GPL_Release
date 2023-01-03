


#include "yard.h"
#include "global.h"


int hmembuf = 0;	
int hmempair = 0;
int hmempeer = 0;
int hmemreq = 0;

int nmembuf = 0;	
int nmempair = 0;
int nmempeer = 0;
int nmemreq = 0;

int tmembuf = 0;	
int tmempair = 0;
int tmempeer = 0;
int tmemreq = 0;



char* ip_hostname(UINT4 ipaddr)
{
	struct	hostent *hp;
	static char	hstname[128];
	UINT4	n_ipaddr;

	n_ipaddr = htonl(ipaddr);
	hp = gethostbyaddr((char *)&n_ipaddr, sizeof (struct in_addr), AF_INET);
	if (hp == 0) {
		ipaddr2str(hstname, sizeof(hstname), ipaddr);
		return(hstname);
	}
	return(hp->h_name);
}



UINT4 get_ipaddr(char *host)
{
	struct hostent *hp;

	if(good_ipaddr(host) == 0) {
		return(ipstr2long(host));
	}
	else if((hp = gethostbyname(host)) == (struct hostent *)NULL) {
		return((UINT4)0);
	}
	return(ntohl(*(UINT4 *)hp->h_addr));
}



int good_ipaddr(char*addr)
{
	int	dot_count;
	int	digit_count;

	dot_count = 0;
	digit_count = 0;
	while(*addr != '\0' && *addr != ' ') {
		if(*addr == '.') {
			dot_count++;
			digit_count = 0;
		}
		else if(!isdigit(*addr)) {
			dot_count = 5;
		}
		else {
			digit_count++;
			if(digit_count > 3) {
				dot_count = 5;
			}
		}
		addr++;
	}
	if(dot_count != 3) {
		return(-1);
	}
	else {
		return(0);
	}
}



void ipaddr2str(char*buffer,size_t buflen,UINT4 ipaddr)
{
	int	addr_byte[4];
	int	i;
	UINT4	xbyte;

	for(i = 0;i < 4;i++) {
		xbyte = ipaddr >> (i*8);
		xbyte = xbyte & (UINT4)0x000000FF;
		addr_byte[i] = xbyte;
	}
	snprintf(buffer, buflen, "%u.%u.%u.%u", addr_byte[3], addr_byte[2],
		addr_byte[1], addr_byte[0]);
}



char*ipaddr2strp(UINT4 ipaddr)
{
	int	addr_byte[4];
	int	i;
	UINT4	xbyte;
	static char buffer[32];

	for(i = 0;i < 4;i++) {
		xbyte = ipaddr >> (i*8);
		xbyte = xbyte & (UINT4)0x000000FF;
		addr_byte[i] = xbyte;
	}
	snprintf(buffer, sizeof(buffer), "%u.%u.%u.%u", addr_byte[3], addr_byte[2],
		addr_byte[1], addr_byte[0]);
	return(buffer);
}




UINT4 ipstr2long(char*ip_str)
{
	char	buf[6];
	char	*ptr;
	int	i;
	int	count;
	UINT4	ipaddr;
	int	cur_byte;

	ipaddr = (UINT4)0;
	for(i = 0;i < 4;i++) {
		ptr = buf;
		count = 0;
		*ptr = '\0';
		while(*ip_str != '.' && *ip_str != '\0' && count < 4) {
			if(!isdigit(*ip_str)) {
				return((UINT4)0);
			}
			*ptr++ = *ip_str++;
			count++;
		}
		if(count >= 4 || count == 0) {
			return((UINT4)0);
		}
		*ptr = '\0';
		cur_byte = atoi(buf);
		if(cur_byte < 0 || cur_byte > 255) {
			return((UINT4)0);
		}
		ip_str++;
		ipaddr = ipaddr << 8 | (UINT4)cur_byte;
	}
	return(ipaddr);
}




char* req2str(char *buffer,size_t buflen,AUTH_REQ *authreq)
{
	int	addr_byte[4];
	int	i;
	UINT4	xbyte;
	UINT4	ipaddr;

	if (buffer == (char *)NULL) {
		return buffer;
	}

	if (authreq == (AUTH_REQ *)NULL) {
		memcpy(buffer,"(unidentified)",15);
		return (buffer);
	}

	ipaddr = authreq->ipaddr;

	for(i = 0;i < 4;i++) {
		xbyte = ipaddr >> (i*8);
		xbyte = xbyte & (UINT4)0x000000FF;
		addr_byte[i] = xbyte;
	}
	snprintf(buffer, buflen, "%u.%u.%u.%u/%u.%u", addr_byte[3], addr_byte[2],
		addr_byte[1], addr_byte[0], authreq->udp_port, authreq->id);

	return(buffer);
}


char* req2strp(AUTH_REQ *authreq)
{
	static char buffer[32];

	return req2str(buffer,sizeof(buffer),authreq);
}




char * bufalloc(int size,char*where)
{
	char 		*buf;

	if((buf = (char *)malloc((unsigned)size)) == (char *)NULL) {
                log_err("%s: fatal system error: out of memory, exiting\n",where);
                rad_exit(-1);
        }

	nmembuf++;
	tmembuf++;
	if (nmembuf > hmembuf) {
		hmembuf = nmembuf;
	}
	if (debug_mem) {
		log_err("called bufalloc(%d,%s) = %x %d\n",size,where,(int)buf,nmembuf);
	}

	return buf;
}





void buffree(char*buf,char*where)
{
	if (debug_mem) {
		log_err("called buffree(%x,%s) = %d\n",(int)buf,where,nmembuf);
	}
        if (buf == (char *)NULL) {
		log_err("%s called buffree with NULL pointer\n",where);
        } else {
                free(buf);
		nmembuf--;
	}
}




VALUE_PAIR *pairalloc(char*where)
{
	VALUE_PAIR	*pair;

	if((pair = (VALUE_PAIR *)malloc(sizeof(VALUE_PAIR))) == (VALUE_PAIR *)NULL) {
                log_err("%s: fatal system error: out of memory, exiting\n",where);
                rad_exit(-1);
        }

        memset(pair,0,sizeof(VALUE_PAIR));
	pair->next = (VALUE_PAIR *)NULL;

	nmempair++;
	tmempair++;
	if (nmempair > hmempair) {
		hmempair = nmempair;
	}

	return pair;

}




void pairfree(VALUE_PAIR*pair,char*where)
{
	VALUE_PAIR	*next;

	while(pair != (VALUE_PAIR *)NULL) {
		next = pair->next;
		memset(pair,0,sizeof(VALUE_PAIR));
		free(pair);
		pair = next;
		nmempair--;
	}
}





PEER * peeralloc(char *where)
{
	PEER		*peer;

	if((peer = (PEER *)malloc(sizeof(PEER))) == (PEER *)NULL) {
                log_err("%s: fatal system error: out of memory, exiting\n",
			where);
                rad_exit(-1);
        }

        memset(peer,0,sizeof(PEER));
	peer->next = (PEER *)NULL;

	nmempeer++;
	tmempeer++;
	if (nmempeer > hmempeer) {
		hmempeer = nmempeer;
	}

	return peer;

}




void peerfree(PEER*peer,char*where)
{
	if (peer == (PEER *)NULL) {
		log_err("%s called peerfree with NULL pointer\n",where);
	} else {
		if (peer->next != (PEER *)NULL) {
			__debug("%s called peerfree with live next pointer\n",
				where);
		}
		memset(peer,0,sizeof(PEER));
		free(peer);
		nmempeer--;
	}
}






AUTH_REQ *reqalloc(char *where)
{
	AUTH_REQ	*authreq;

	if((authreq = (AUTH_REQ *)malloc(sizeof(AUTH_REQ))) == (AUTH_REQ *)NULL) {
                log_err("%s: fatal system error: out of memory, exiting\n",where);
                rad_exit(-1);
        }

        memset(authreq,0,sizeof(AUTH_REQ));
	authreq->request = (VALUE_PAIR *)NULL;
	authreq->next = (AUTH_REQ *)NULL;
	authreq->packet = (char *)NULL;

	nmemreq++;
	tmemreq++;
	if (nmemreq > hmemreq) {
		hmemreq = nmemreq;
	}
	if (debug_mem) {
		log_err("called reqalloc(%s) = %x %d\n",where,(int)authreq,nmemreq);
	}

	return authreq;

}





void reqfree( AUTH_REQ*authreq,char*where)
{
	if (debug_mem) {
		log_err("called reqfree(%x,%s) = %d\n",(int)authreq,where,nmemreq);
	}
        if (authreq == (AUTH_REQ *)NULL) {
		log_err("%s called reqfree with NULL pointer\n",where);
        } else {
                pairfree(authreq->request,where);
		if (authreq->packet != (char *) NULL) {
			buffree(authreq->packet,where);
		}
                memset(authreq, 0, sizeof(AUTH_REQ));
                free(authreq);
		nmemreq--;
	}
}

void memreport(void)
{
	log_err("memory usage = pair %d/%d/%d  peer %d/%d/%d  req %d/%d/%d  buf %d/%d/%d\n",
	nmempair,hmempair,tmempair, nmempeer,hmempeer,tmempeer, 
	nmemreq,hmemreq,tmemreq, nmembuf,hmembuf,tmembuf );
     
}




void fprint_attr_val(FILE*fd,VALUE_PAIR*pair)
{
	DICT_VALUE	*dval;
	char		buffer[32];
	char		prtbuf[1060];
	int		len;
	u_char		*ptr;

	switch(pair->type) {

	case PW_TYPE_STRING:
		snprintf(prtbuf,sizeof(prtbuf),"%s = \"", pair->name);
		ptr = (u_char *)pair->strvalue;
		len = pair->lvalue;
		if ( ptr[len-1]=='\0' ) len--; 
		while(len-- > 0) {
			if(!(isprint(*ptr))) {
				snprintf(buffer,sizeof(buffer),"\\%03o", *ptr);
				strcat(prtbuf, buffer);
			}
			else {
				fprint_attr_putc(*ptr, (u_char*)prtbuf);
			}
			ptr++;
		}
		fprint_attr_putc('"', (u_char *)prtbuf);
		break;
			
	case PW_TYPE_INTEGER:
		dval = dict_valget(pair->lvalue, pair->name);
		if(dval != (DICT_VALUE *)NULL) {
			snprintf(prtbuf,sizeof(prtbuf),"%s = %s", pair->name, dval->name);
		}
		else {
			snprintf(prtbuf,sizeof(prtbuf),"%s = %ld", pair->name, pair->lvalue);
		}
		break;

	case PW_TYPE_IPADDR:
		ipaddr2str(buffer,sizeof(buffer),pair->lvalue);
		snprintf(prtbuf,sizeof(prtbuf),"%s = %s", pair->name, buffer);
		break;

	case PW_TYPE_DATE:
		strftime(buffer, sizeof(buffer), "%b %e %Y",
					gmtime((time_t *)&pair->lvalue));
		snprintf(prtbuf,sizeof(prtbuf),"%s = \"%s\"", pair->name, buffer);
		break;

	default:
		snprintf(prtbuf,sizeof(prtbuf),"Unknown type %d", pair->type);
		break;
	}
	if (fd == (FILE *)-1) {

		log_debug("%s\n", prtbuf);
	} else {
	}
}

void fprint_attr_putc(u_char cc,u_char *buf)
{
	int len;

	len = strlen((const char *)buf);
	buf[len] = cc;
	buf[len+1] = (u_char)0;
}




void hexdump(u_char*buf,int n)
{
	int i;
	int j;
	char s[64];

	if (n > 200) {
		n = 200;
	}
	s[48] = '\n';
	s[48] = '\0';
	for (i = 0; i < n; i++) {	
		j = i & 0x0f;
		sprintf(&s[3*j],"%02x ",(int)buf[i]);
		if (j == 15) {
			log_debug("%s\n",s);
		}
	}
	if (n > 0 && j < 15) {
		s[3*j+3] = '\n';
		s[3*j+3] = '\0';
		log_debug("%s\n",s);
	}

}
