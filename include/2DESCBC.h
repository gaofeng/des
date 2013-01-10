// HEADER FILE 2DESCBC.h.

#ifndef DESCBC2
#define DESCBC2

#include "DESCBC.h"
#include "2DES.h"


DataChunk DESCBC2Encrypt(DataChunk message, Block key1, Block key2);
DataChunk DESCBC2Decrypt(DataChunk cipherText, Block key1, Block key2);


#endif

