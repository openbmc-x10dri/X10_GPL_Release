


#include "yard.h"
#include "global.h"

static DICT_ATTR	*dictionary_vendors;
static DICT_ATTR	*dictionary_attributes;
static DICT_VALUE	*dictionary_values;



int dict_init(void)
{
	FILE	*dictfd;
	char	dummystr[64];
	char	namestr[64];
	char	valstr[64];
	char	attrstr[64];
	char	typestr[64];
	char	vendorstr[64];
	int	line_no;
	DICT_ATTR	*attr;
	DICT_VALUE	*dval;
	char	buffer[256];
	char	dictfile[PATH_MAX];
	int	value;
	int	type;

	snprintf(dictfile,PATH_MAX, "%s/%s", radius_dir, RADIUS_DICTIONARY);
	if((dictfd = fopen(dictfile, "r")) == (FILE *)NULL) {
		log_err("could not read dictionary file %s\n",dictfile);
		return(-1);
	}

	line_no = 0;
	while(fgets(buffer, sizeof(buffer), dictfd) != (char *)NULL) {
		line_no++;
		
		if(*buffer == '#' || *buffer == '\0' || *buffer == '\n') {
			continue;
		}

		if(strncmp(buffer, "ATTRIBUTE", 9) == 0) {
			vendorstr[0] = '\0';
			if(sscanf(buffer, "%s%s%s%s%s", dummystr, namestr,
					valstr, typestr,vendorstr) < 4) {
				log_err("invalid attribute on line %d of dictionary file %s\n", line_no,dictfile);
				return(-1);
			}


			if((int)strlen(namestr) > 31) {
				log_err("attribute name too long on line %d of dictionary %s\n",
					line_no, dictfile);
				return(-1);
			}

			if(!isdigit(*valstr)) {
				log_err("attribute has non-numeric value on line %d of dictionary %s\n", line_no, dictfile);
				return(-1);
			}
			value = strtol(valstr,(char**)NULL,0);

			if(strcmp(typestr, "string") == 0) {
				type = PW_TYPE_STRING;
			}
			else if(strcmp(typestr, "integer") == 0) {
				type = PW_TYPE_INTEGER;
			}
			else if(strcmp(typestr, "ipaddr") == 0) {
				type = PW_TYPE_IPADDR;
			}
			else if(strcmp(typestr, "date") == 0) {
				type = PW_TYPE_DATE;
			}
			else {
				log_err("attribute has unknown type on line %d of dictionary %s\n", line_no, dictfile);
				return(-1);
			}

			if((attr = (DICT_ATTR *)malloc(sizeof(DICT_ATTR))) ==
					(DICT_ATTR *)NULL) {
				log_err("ran out of memory after reading line %d of dictionary %s\n",line_no,dictfile);
				return(-1);
			}
			strcpy(attr->name, namestr);
			attr->type = type;
			if (*vendorstr) {	
				attr->value = PW_VENDOR;
				attr->vsvalue = value;
				attr->vendor = dict_vendor(vendorstr);
			}
			else {
				attr->value = value;
				attr->vsvalue = 0;
				attr->vendor = 0;
			}

			attr->next = dictionary_attributes;
			dictionary_attributes = attr;
		}
		else if(strncmp(buffer, "VALUE", 5) == 0) {

			if(sscanf(buffer, "%s%s%s%s", dummystr, attrstr,
						namestr, valstr) != 4) {
				log_err("Invalid value entry on line %d of dictionary %s\n", line_no, dictfile);
				return(-1);
			}


			if((int)strlen(attrstr) > 31) {
				log_err("attribute name too long on line %d of dictionary %s\n", line_no, dictfile);
				return(-1);
			}

			if((int)strlen(namestr) > 31) {
				log_err("value name too long on line %d of dictionary %s\n", line_no, dictfile);
				return(-1);
			}

			if(!isdigit(*valstr)) {
				log_err("value has non-numeric value on line %d of dictionary %s\n", line_no, dictfile);
				return(-1);
			}
			value = atoi(valstr);

			if((dval = (DICT_VALUE *)malloc(sizeof(DICT_VALUE))) ==
					(DICT_VALUE *)NULL) {
				log_err("ran out of memory after reading line %d of dictionary %s\n",line_no,dictfile);
				return(-1);
			}
			strcpy(dval->attrname, attrstr);
			strcpy(dval->name, namestr);
			dval->value = value;

			dval->next = dictionary_values;
			dictionary_values = dval;
		}
		else if(strncmp(buffer, "VENDOR", 6) == 0) {
			if(sscanf(buffer, "%s%s%s", dummystr, namestr,
					valstr) < 3) {
				log_err("invalid vendor on line %d of dictionary file %s\n", line_no, dictfile);
				return(-1);
			}


			if((int)strlen(namestr) > 31) {
				log_err("vendor name too long on line %d of dictionary %s\n",
					line_no, dictfile);
				return(-1);
			}

			if(!isdigit(*valstr)) {
				log_err("vendor \"%s\" has non-numeric value \"%s\" on line %d of dictionary %s\n", namestr, valstr, line_no, dictfile);
				return(-1);
			}
			value = atoi(valstr);

			if((attr = (DICT_ATTR *)malloc(sizeof(DICT_ATTR))) ==
					(DICT_ATTR *)NULL) {
				log_err("ran out of memory after reading line %d of dictionary %s\n",line_no,dictfile);
				return(-1);
			}
			strcpy(attr->name, namestr);
			attr->vendor = value;
			attr->type = 0;
			attr->value = 0;
			attr->vsvalue = 0;

			attr->next = dictionary_vendors;
			dictionary_vendors = attr;
		}
	}
	fclose(dictfd);
	return(0);
}



DICT_ATTR*dict_attrget(int attribute)
{
	DICT_ATTR	*attr;

	attr = dictionary_attributes;
	while(attr != (DICT_ATTR *)NULL) {
		if(attr->value == attribute) {
			return(attr);
		}
		attr = attr->next;
	}
	return((DICT_ATTR *)NULL);
}



DICT_ATTR*dict_vsattrget(int vendor,int vsa)
{
	DICT_ATTR	*attr;

	attr = dictionary_attributes;
	while(attr != (DICT_ATTR *)NULL) {
		if(attr->value == PW_VENDOR &&
		   attr->vendor == vendor &&
		   attr->vsvalue == vsa) {
			return(attr);
		}
		attr = attr->next;
	}
	return((DICT_ATTR *)NULL);
}



DICT_ATTR*dict_attrfind(char*attrname)
{
	DICT_ATTR	*attr;

	attr = dictionary_attributes;
	while(attr != (DICT_ATTR *)NULL) {
		if(strcmp(attr->name, attrname) == 0) {
			return(attr);
		}
		attr = attr->next;
	}
	return((DICT_ATTR *)NULL);
}



DICT_VALUE*dict_valfind(char *valname)
{
	DICT_VALUE	*val;

	val = dictionary_values;
	while(val != (DICT_VALUE *)NULL) {
		if(strcmp(val->name, valname) == 0) {
			return(val);
		}
		val = val->next;
	}
	return((DICT_VALUE *)NULL);
}



DICT_VALUE*dict_valget(UINT4 value,char*attrname)
{
	DICT_VALUE	*val;

	val = dictionary_values;
	while(val != (DICT_VALUE *)NULL) {
		if(strcmp(val->attrname, attrname) == 0 &&
						(unsigned int)val->value == value) {
			return(val);
		}
		val = val->next;
	}
	return((DICT_VALUE *)NULL);
}



int dict_vendor(char *vendname)
{
	DICT_ATTR	*vend;

	vend = dictionary_vendors;
	while (vend != (DICT_ATTR *)NULL) {
		if (strcmp(vend->name, vendname) == 0) {
			return(vend->vendor);
		}
		vend = vend->next;
	}
	return(atoi(vendname));
}



void dict_dump(void)
{
  DICT_ATTR *ap;

  if (!debug_flag) return;


  log_debug( "Starting dumping of Vendors Dictionary\n\n" );
  for ( ap=dictionary_vendors; ap!=NULL; ap=ap->next )
    log_debug("Vendor-name %s, vendor-id %d\n",ap->name,ap->vendor);


  log_debug( "Starting dumping of Attributes Dictionary\n\n" );
  for ( ap=dictionary_attributes; ap!=NULL; ap=ap->next )
    log_debug("Attr %s, value %d, vsvalue %d, type %d, vendor %d\n",
              ap->name,ap->value,ap->vsvalue,ap->type,ap->vendor);
}
