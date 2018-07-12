#define RSCODE_FLIR_INTERNAL
#include "ecc.h"
#include "rs.h"
#include "berlekamp.h"

void rscode_init(struct rscode_driver * driver)
{
  initialize_ecc (driver);
}

void rscode_encode(struct rscode_driver * driver, unsigned char *msg, int nbytes, unsigned char *dst)
{
  encode_data (driver, msg, nbytes,dst);
}

int rscode_decode(struct rscode_driver * driver, unsigned char *data, int nbytes)
{
  decode_data(driver, data, nbytes);
  int ret = check_syndrome (driver);
  if(ret!=0)
  {
    correct_errors_erasures (driver, data, 
           nbytes,
           0, 
           0);
  }
  return ret;
}
