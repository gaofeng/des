// SOURCE FILE CONTAINING 2DES ROUTINES IN CBC MODE.

#include "2DESCBC.h"


DataChunk DESCBC2Encrypt(DataChunk messageChunk, Block key1, Block key2)
{
	DataChunk cipherChunk = initDataChunk(messageChunk.iLength - messageChunk.iLength % 8 + 16);
	Block message = initBlock(64), cipher;
	KeySchedule k1, k2;
	int i;

	cipher = generateIV();
	k1 = DESKeySchedule(key1);
	k2 = DESKeySchedule(key2);
	for (i = 0; i < messageChunk.iLength / 8; i++) {
		memcpy(cipherChunk.block + 8 * i, cipher, 8);
		memcpy(message, messageChunk.block + 8 * i, 8);
		cipher = DES2Encrypt(blockXOR(message, cipher, 64), k1, k2);
	}
	memcpy(cipherChunk.block + 8 * i, cipher, 8);
	free(message);

	// If the length is not an integral multiple of 8.
	if (messageChunk.iLength % 8) {
		memcpy((message = initBlock(64)), messageChunk.block + 8 * i, messageChunk.iLength % 8);
		cipher = DES2Encrypt(blockXOR(message, cipher, 64), k1, k2);
		memcpy(cipherChunk.block + 8 * (i + 1), cipher, 8);
	}

	return (cipherChunk);
}


DataChunk DESCBC2Decrypt(DataChunk cipherChunk, Block key1, Block key2)
{
	DataChunk messageChunk = initDataChunk(cipherChunk.iLength - 8);
	Block message, cipher = initBlock(64);
	KeySchedule k1, k2;
	int i, j;

	k1 = DESKeySchedule(key1);
 	k2 = DESKeySchedule(key2);
	for (i = 0; i < messageChunk.iLength / 8; i++) {
		memcpy(cipher, cipherChunk.block + 8 * i, 8);
		message = blockXOR(cipher, DES2Decrypt(cipherChunk.block + 8 * (i + 1), k1, k2), 64);
		memcpy(messageChunk.block + 8 * i, message, 8);
	}

	// Eliminate the effect of zero padding.
	for (i = messageChunk.iLength - 1; i >= 0 && messageChunk.block[i] == 0; i--)
		(messageChunk.iLength)--;

	return (messageChunk);
}


