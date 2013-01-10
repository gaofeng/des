// SOURCE FILE CONTAINING DES ROUTINES IN CBC MODE.

#include "DESCBC.h"


DataChunk initDataChunk(int iLength)
{
	DataChunk dataChunk;

	dataChunk.block = (Block) malloc(iLength * sizeof (uChar));
	dataChunk.iLength = iLength;

	return (dataChunk);
}


Block generateIV()
{
	Block IV = initBlock(64);
	int i;

IV[0] = 0x00;
IV[1] = 0x22;
IV[2] = 0x44;
IV[3] = 0x66;
IV[4] = 0x88;
IV[5] = 0xaa;
IV[6] = 0xcc;
IV[7] = 0xee;



/*
	for (i = 0; i < 8; i++)
		IV[i] = (char) (rand() % (UCHAR_MAX + 1));
*/
	return (IV);
}


DataChunk DESCBCEncrypt(DataChunk messageChunk, Block key)
{
	DataChunk cipherChunk = initDataChunk(messageChunk.iLength - messageChunk.iLength % 8 + 16);
	Block message = initBlock(64), cipher;
	KeySchedule k;
	int i;

	cipher = generateIV();
	k = DESKeySchedule(key);
	for (i = 0; i < messageChunk.iLength / 8; i++) {
		memcpy(cipherChunk.block + 8 * i, cipher, 8);
		memcpy(message, messageChunk.block + 8 * i, 8);
		cipher = DESEncrypt(blockXOR(message, cipher, 64), k);
	}
	memcpy(cipherChunk.block + 8 * i, cipher, 8);
	free(message);

	// If the length is not an integral multiple of 8.
	if (messageChunk.iLength % 8) {
		memcpy((message = initBlock(64)), messageChunk.block + 8 * i, messageChunk.iLength % 8);
		cipher = DESEncrypt(blockXOR(message, cipher, 64), k);
		memcpy(cipherChunk.block + 8 * (i + 1), cipher, 8);
	}

	return (cipherChunk);
}


DataChunk DESCBCDecrypt(DataChunk cipherChunk, Block key)
{
	DataChunk messageChunk = initDataChunk(cipherChunk.iLength - 8);
	Block message, cipher = initBlock(64);
	KeySchedule k;
	int i, j;

	k = DESKeySchedule(key);
	for (i = 0; i < messageChunk.iLength / 8; i++) {
		memcpy(cipher, cipherChunk.block + 8 * i, 8);
		message = blockXOR(cipher, DESDecrypt(cipherChunk.block + 8 * (i + 1), k), 64);
		memcpy(messageChunk.block + 8 * i, message, 8);
	}

	// Eliminate the effect of zero padding.
	for (i = messageChunk.iLength - 1; i >= 0 && messageChunk.block[i] == 0; i--)
		(messageChunk.iLength)--;

	return (messageChunk);
}

