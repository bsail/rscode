/*****************************
 * Copyright Henry Minsky (hqm@alum.mit.edu) 1991-2009
 *
 * This software library is licensed under terms of the GNU GENERAL
 * PUBLIC LICENSE
 *
 * RSCODE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RSCODE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Rscode.  If not, see <http://www.gnu.org/licenses/>.

 * Commercial licensing is available under a separate license, please
 * contact author for details.
 *
 * Source code is available at http://rscode.sourceforge.net
 * 
 *
 * Multiplication and Arithmetic on Galois Field GF(256)
 *
 * From Mee, Daniel, "Magnetic Recording, Volume III", Ch. 5 by Patel.
 * 
 *
 ******************************/
 
#define RSCODE_INTERNAL
#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include "ecc.h"

/* This is one of 14 irreducible polynomials
 * of degree 8 and cycle length 255. (Ch 5, pp. 275, Magnetic Recording)
 * The high order 1 bit is implicit */
/* x^8 + x^4 + x^3 + x^2 + 1 */
#define PPOLY 0x1D 

static void init_exp_table (struct rscode_driver * driver);


void
init_galois_tables (struct rscode_driver * driver)
{	
  /* initialize the table of powers of alpha */
  init_exp_table(driver);
}


static void
init_exp_table (struct rscode_driver * driver)
{
  int i, z;
  int pinit,p1,p2,p3,p4,p5,p6,p7,p8;

  pinit = p2 = p3 = p4 = p5 = p6 = p7 = p8 = 0;
  p1 = 1;
	
  driver->gexp[0] = 1;
  driver->gexp[255] = driver->gexp[0];
	
  for (i = 1; i < 256; i++) {
    pinit = p8;
    p8 = p7;
    p7 = p6;
    p6 = p5;
    p5 = p4 ^ pinit;
    p4 = p3 ^ pinit;
    p3 = p2 ^ pinit;
    p2 = p1;
    p1 = pinit;
    driver->gexp[i] = p1 + p2*2 + p3*4 + p4*8 + p5*16 + p6*32 + p7*64 + p8*128;
    driver->gexp[i+255] = driver->gexp[i];
  }
}

static int glog(struct rscode_driver * driver, int value)
{
  int z;
  int ret = 0;

  for (z = 0; z < 256; z++) {
    if (driver->gexp[z] == value) {
      ret = z;
      break;
    }
  }

  return ret;
}

/* multiplication using logarithms */
int gmult(struct rscode_driver * driver, int a, int b)
{
  int i,j;
  if (a==0 || b == 0) return (0);
  i = glog(driver,a);
  j = glog(driver,b);
  return (driver->gexp[i+j]);
}
		

int ginv (struct rscode_driver * driver, int elt) 
{ 
  return (driver->gexp[255-glog(driver,elt)]);
  // return (driver->gexp[255-driver->glog[elt]]);
}

