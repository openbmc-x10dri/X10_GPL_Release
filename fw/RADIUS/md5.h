


#ifndef PROTOTYPES
#define PROTOTYPES 0
#endif

typedef unsigned char *POINTER;

typedef unsigned short int UINT2;



#if PROTOTYPES
#define PROTO_LIST(list) list
#else
#define PROTO_LIST(list) ()
#endif





typedef struct {
  UINT4 state[4];                                   
  UINT4 count[2];        
  unsigned char buffer[64];                         
} MD5_CTX;

void MD5Init (MD5_CTX *context);
void MD5Update (MD5_CTX *context, unsigned char * input, unsigned int inputLen);
void MD5Final (unsigned char digest[16], MD5_CTX *context);

