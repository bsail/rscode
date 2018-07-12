#ifndef _BERLEKAMP_H
#define _BERLEKAMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ecc.h"

#ifndef TEST
#ifndef RSCODE_FLIR_INTERNAL
#error "There is no user accessable data and functions here"
#endif
#endif

/* polynomial arithmetic */
void copy_poly(int dst[], int src[]);

void add_polys(int dst[], int src[]) ;
void scale_poly(int k, int poly[]);
void mult_polys(int dst[], int p1[], int p2[]);

void zero_poly(int poly[]);

/* Error location routines */
int correct_errors_erasures (unsigned char codeword[], int csize,int nerasures, int erasures[]);

#ifdef __cplusplus
}
#endif

#endif // _BERLEKAMP_H
