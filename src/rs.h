#ifndef _RS_H
#define _RS_H

#include "ecc.h"

/* print debugging info */
int DEBUG;

/* Decoder syndrome bytes */
int synBytes[MAXDEG];

/* Encoder parity bytes */
int pBytes[MAXDEG];

/* Reed Solomon encode/decode routines */
void initialize_ecc (void);
int check_syndrome (void);
void decode_data (unsigned char data[], int nbytes);
void encode_data (unsigned char msg[], int nbytes, unsigned char dst[]);

#endif // _RS_H
