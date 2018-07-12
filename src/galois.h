#ifndef _GALOIS_H
#define _GALOIS_H

#include "ecc.h"

/* galois arithmetic tables */
int gexp[512];
int glog[256];;

void init_galois_tables (void);
int gmult(int a, int b);
int ginv(int elt);

#endif // _GALOIS_H
