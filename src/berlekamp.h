#ifndef _BERLEKAMP_H
#define _BERLEKAMP_H

#include "ecc.h"

/* polynomial arithmetic */
void copy_poly(int dst[], int src[]);

void add_polys(int dst[], int src[]) ;
void scale_poly(int k, int poly[]);
void mult_polys(int dst[], int p1[], int p2[]);

void zero_poly(int poly[]);

/* Error location routines */
int correct_errors_erasures (unsigned char codeword[], int csize,int nerasures, int erasures[]);

#endif // _BERLEKAMP_H
