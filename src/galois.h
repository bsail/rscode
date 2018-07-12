#ifndef _GALOIS_H
#define _GALOIS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ecc.h"

#ifndef TEST
#ifndef RSCODE_FLIR_INTERNAL
#error "There is no user accessable data and functions here"
#endif
#endif

/* galois arithmetic tables */
int gexp[512];
int glog[256];;

void init_galois_tables (void);
int gmult(int a, int b);
int ginv(int elt);

#ifdef __cplusplus
}
#endif

#endif // _GALOIS_H
