#include "ecc.h"
#include "rs.h"
#include "berlekamp.h"

void rscode_init(void)
{
  initialize_ecc ();
}

void rscode_encode(unsigned char *msg, int nbytes, unsigned char *dst)
{
  encode_data (msg, nbytes,dst);
}

int rscode_decode(unsigned char *data, int nbytes)
{
  decode_data(data, nbytes);
  int ret = check_syndrome ();
  if(ret!=0)
  {
    correct_errors_erasures (data, 
           nbytes,
           0, 
           0);
  }
  return ret;
}
