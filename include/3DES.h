// HEADER FILE 3DES.h.

#ifndef DES3
#define DES3

#include "DES.h"

Block DES3Encrypt(Block message, KeySchedule k1, KeySchedule k2);
Block DES3Decrypt(Block cipher, KeySchedule k1, KeySchedule k2);

#endif

