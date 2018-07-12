#ifndef _RS_H
#define _RS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ecc.h"

#ifndef TEST
#ifndef RSCODE_FLIR_INTERNAL
#error "There is no user accessable data and functions here"
#endif
#endif

/* Decoder syndrome bytes */
int synBytes[MAXDEG];

/* Encoder parity bytes */
int pBytes[MAXDEG];

/* Reed Solomon encode/decode routines */
void initialize_ecc (void);
int check_syndrome (void);
void decode_data (unsigned char *data, int nbytes);
void encode_data (unsigned char *msg, int nbytes, unsigned char *dst);

#ifdef __cplusplus
}
#endif

#endif // _RS_H
