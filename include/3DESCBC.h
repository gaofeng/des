// HEADER FILE 3DESCBC.h.

#ifndef DESCBC3
#define DESCBC3

#include "DESCBC.h"
#include "3DES.h"


DataChunk DESCBC3Encrypt(DataChunk message, Block key1, Block key2);
DataChunk DESCBC3Decrypt(DataChunk cipherText, Block key1, Block key2);


#endif

