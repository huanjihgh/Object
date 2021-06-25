#ifndef __CRYPT_SHA1_H_
#define __CRYPT_SHA1_H_

#include <cstdint>

#define SHA1_DIGEST_SIZE 20

void
crypt_sha1(uint8_t* buffer, int sz, uint8_t* output, int& e_sz);


#endif

