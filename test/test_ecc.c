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
#include <alloca.h>

#define LENGTH 48
unsigned char msg_example[256];

void setUp(void)
{
  time_t t;
  srand((unsigned) time(&t));
  strcpy((char*)msg_example,"=0123456789abcdefghijklmnopqrstuwvzyx0123456789=");
}

void tearDown(void)
{
}

void test_ecc_should_work_simple(void)
{
  uint8_t length = LENGTH;
  struct rscode_driver driver;

  unsigned char codeword[256];
  unsigned char newword[256];
  unsigned char *msg = alloca(length);
  memcpy(msg,msg_example,length);
  printf("=== BEGIN test_ecc_should_work_simple ===\n");
  printf("Original message:");
  for(int i=0;i<length;++i)
    printf("%c",msg[i]);
  printf("\n");

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

static int searh_in_erasures(int value, int nerasures, int * erasures)
{
  int ret = 0;
  for(int i=0;i<nerasures;++i) {
    if(erasures[i]==value){
      ret = 1;
      break;
    }
  }
  return ret;
}

void test_ecc_should_work_with_erasures(void)
{
  uint8_t length = LENGTH;
  #define NERASURES (NPAR/2-4)

  struct rscode_driver driver;

  unsigned char codeword[256];
  unsigned char newword[256];
  unsigned char *msg = alloca(length);
  memcpy(msg,msg_example,length);
  printf("=== BEGIN test_ecc_should_work_with_erasures ===\n");
  printf("Original message:");
  for(int i=0;i<length;++i)
    printf("%c",msg[i]);
  printf("\n");
   
  rscode_init(&driver);
  /* Encode data into codeword, adding NPAR parity bytes */
  rscode_encode(&driver, msg, length, codeword);

  printf("Encoded message: ");
  for(int i=0;i<length;++i)
    printf("%c",codeword[i]);
  printf("\n");
 
  uint8_t ML = (length + NPAR);

  int nerasures = 0;
  int erasures[NERASURES];

  for(int i=0;i<(NERASURES);++i)
  {
    unsigned char position_random = rand();
    int position = roundl((position_random*ML)/255.0);
    while(searh_in_erasures(position_random,nerasures,erasures)==1)
    {
      position_random = rand();
      position = roundl((position_random*ML)/255.0);
    }
    unsigned char value_random = rand();
    unsigned char value = roundl((value_random*40.0)/255.0);
    erasures[nerasures++] = ML-position-1;
    codeword[position] = '0'+value;
    // printf("Erasure at loc %d, data %#x\n", position, codeword[position]);
  }

  memcpy(newword,codeword,256);
  nerasures = NPAR/4;

  printf("Affected message:");
  for(int i=0;i<length;++i)
    printf("%c",newword[i]);
  printf("\n");

  int ret = rscode_decode_with_erasures(&driver, newword, ML, nerasures, erasures);

  printf("Decoded message: ");
  for(int i=0;i<length;++i)
    printf("%c",newword[i]);
  printf("\n");

  printf("=== END test_ecc_should_work_with_erasures ===\n");

  TEST_ASSERT_NOT_EQUAL(0,ret);
  TEST_ASSERT_EQUAL_MEMORY(msg,newword,length);
}

void test_ecc_should_not_work_with_erasures_out_of_bounds(void)
{
  uint8_t length = LENGTH;

  struct rscode_driver driver;

  unsigned char codeword[256];
  unsigned char newword[256];
  unsigned char *msg = alloca(length);
  memcpy(msg,msg_example,length);
   
  rscode_init(&driver);
  /* Encode data into codeword, adding NPAR parity bytes */
  rscode_encode(&driver, msg, length, codeword);

  uint8_t ML = (length + NPAR);

  int nerasures = 0;
  int erasures[NPAR];

  for(int i=0;i<(NPAR/2);++i)
  {
    unsigned char position_random = rand();
    int position = roundl((position_random*ML)/255.0);
    while(searh_in_erasures(position_random,nerasures,erasures)==1)
    {
      position_random = rand();
      position = roundl((position_random*ML)/255.0);
    }
    unsigned char value_random = rand();
    unsigned char value = roundl((value_random*40.0)/255.0);
    erasures[nerasures++] = ML-position-1;
    codeword[position] = '0'+value;
  }

  memcpy(newword,codeword,256);
  nerasures = NPAR/4;
  erasures[0] = ML+5;

  // #pragma message "FIXME:Should be not equal to 1"
  TEST_ASSERT_NOT_EQUAL(1,rscode_decode_with_erasures(&driver, newword, ML, nerasures, erasures));
}

void test_ecc_should_not_work_with_erasures_too_many_errors(void)
{
  uint8_t length = LENGTH;

  struct rscode_driver driver;

  unsigned char codeword[256];
  unsigned char newword[256];
  unsigned char *msg = alloca(length);
  memcpy(msg,msg_example,length);

  printf("=== BEGIN test_ecc_should_not_work_with_erasures_too_many_errors ===\n");
  printf("Original message:");
  for(int i=0;i<length;++i)
    printf("%c",msg[i]);
  printf("\n");

  rscode_init(&driver);
  /* Encode data into codeword, adding NPAR parity bytes */
  rscode_encode(&driver, msg, length, codeword);

  printf("Encoded message: ");
  for(int i=0;i<length;++i)
    printf("%c",codeword[i]);
  printf("\n");

  uint8_t ML = (length + NPAR);

  int nerasures = 0;
  int erasures[NPAR*3];

  for(int i=0;i<(NPAR*3);++i)
  {
    unsigned char position_random = rand();
    int position = roundl((position_random*ML)/255.0);
    while(searh_in_erasures(position_random,nerasures,erasures)==1)
    {
      position_random = rand();
      position = roundl((position_random*ML)/255.0);
    }
    unsigned char value_random = rand();
    unsigned char value = roundl((value_random*40.0)/255.0);
    erasures[nerasures++] = ML-position-1;
    codeword[position] = '0'+value;
  }

  memcpy(newword,codeword,256);

  printf("Affected message:");
  for(int i=0;i<length;++i)
    printf("%c",newword[i]);
  printf("\n");
  
  int ret = rscode_decode_with_erasures(&driver, newword, ML, nerasures, erasures);

  printf("Decoded message: ");
  for(int i=0;i<length;++i)
    printf("%c",newword[i]);
  printf("\n");

  printf("=== END test_ecc_should_work_with_erasures ===\n");


  // #pragma message "FIXME:Should be not equal to 1"
  TEST_ASSERT_NOT_EQUAL(1,ret);
}
