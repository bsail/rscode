#ifndef _CRCGEN_H
#define _CRCGEN_H

#include "ecc.h"

/* CRC-CCITT checksum generator */
BIT16 crc_ccitt(unsigned char *msg, int len);

#endif // _CRCGEN_H
