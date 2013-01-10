// HEADER FILE DESCBC.h.

#ifndef DESCBC1
#define DESCBC1

#include <limits.h>
#include "DES.h"


typedef struct {
	Block block;
	int iLength;
} DataChunk;


DataChunk initDataChunk(int iLength);
Block generateIV();

DataChunk DESCBCEncrypt(DataChunk message, Block key);
DataChunk DESCBCDecrypt(DataChunk cipherText, Block key);


#endif
