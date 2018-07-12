#include "unity.h"
#include "ecc.h"
#include "rs.h"
#include "galois.h"
#include "berlekamp.h"
#include <time.h>
#include <math.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void setUp(void)
{
}

void tearDown(void)
{
}

#define LENGTH 48
const unsigned char *msg_example = "=0123456789abcdefghijklmnopqrstuwvzyx0123456789=";

void test_ecc_should_work_simple(void)
{
  uint8_t length = LENGTH;
  time_t t;
  struct rscode_driver driver;

  unsigned char codeword[256];
  unsigned char newword[256];
  unsigned char *msg = malloc(length);
  memcpy(msg,msg_example,length);
  printf("=== BEGIN test_ecc_should_work_simple ===\n");
  printf("Original message:");
  for(int i=0;i<length;++i)
    printf("%c",msg[i]);
  printf("\n");

  srand((unsigned) time(&t));
 
  rscode_init(&driver);
  /* Encode data into codeword, adding NPAR parity bytes */
  rscode_encode(&driver, msg, length, codeword);

  printf("Encoded message: ");
  for(int i=0;i<length;++i)
    printf("%c",codeword[i]);
  printf("\n");
 
  uint8_t ML = (length + NPAR);

  for(int i=0;i<(NPAR/2);++i)
  {
    unsigned char position_random = rand();
    unsigned char value_random = rand();
    unsigned char value = roundl((value_random*40.0)/255.0);
    int position = roundl((position_random*ML)/255.0);
    codeword[position] = '0'+value;
  }

  memcpy(newword,codeword,256);

  printf("Affected message:");
  for(int i=0;i<length;++i)
    printf("%c",newword[i]);
  printf("\n");

  TEST_ASSERT_NOT_EQUAL(0,rscode_decode(&driver, newword, ML));

  printf("Decoded message: ");
  for(int i=0;i<length;++i)
    printf("%c",newword[i]);
  printf("\n");

  printf("=== END test_ecc_should_work_simple ===\n");

  TEST_ASSERT_EQUAL_MEMORY(msg,newword,length);
}
