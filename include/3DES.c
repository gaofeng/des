// SOURCE FILE CONTAINING 2DES ROUTINES.

#include "3DES.h"

Block DES3Encrypt(Block message, KeySchedule k1, KeySchedule k2)
{
	return (DESEncrypt(DESDecrypt(DESEncrypt(message, k1), k2), k1));
}


Block DES3Decrypt(Block cipher, KeySchedule k1, KeySchedule k2)
{
	return (DESDecrypt(DESEncrypt(DESDecrypt(cipher, k1), k2), k1));
}


