// HEADER FILE 2DES.h.

#ifndef DES2
#define DES2

#include "DES.h"

Block DES2Encrypt(Block message, KeySchedule k1, KeySchedule k2);
Block DES2Decrypt(Block cipher, KeySchedule k1, KeySchedule k2);

#endif

