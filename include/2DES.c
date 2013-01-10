// SOURCE FILE CONTAINING 2DES ROUTINES.

#include "2DES.h"


Block DES2Encrypt(Block message, KeySchedule k1, KeySchedule k2)
{
	return (DESEncrypt(DESEncrypt(message, k1), k2));
}


Block DES2Decrypt(Block cipher, KeySchedule k1, KeySchedule k2)
{
	return (DESDecrypt(DESDecrypt(cipher, k2), k1));
}

