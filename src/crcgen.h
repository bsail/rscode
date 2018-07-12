#ifndef _CRCGEN_H
#define _CRCGEN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ecc.h"

#ifndef TEST
#ifndef RSCODE_FLIR_INTERNAL
#error "There is no user accessable data and functions here"
#endif
#endif

/* CRC-CCITT checksum generator */
BIT16 crc_ccitt(unsigned char *msg, int len);

#ifdef __cplusplus
}
#endif

#endif // _CRCGEN_H
