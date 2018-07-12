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

void init_galois_tables (struct rscode_driver * driver);
int gmult(struct rscode_driver * driver, int a, int b);
int ginv(struct rscode_driver * driver, int elt);

#ifdef __cplusplus
}
#endif

#endif // _GALOIS_H
