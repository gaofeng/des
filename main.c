// APPLICATION PROGRAM FOR DES ROUTINES.
#include <stdio.h>
#include <string.h>
#include "./include/DES.h"
#include "./include/2DES.h"
#include "./include/3DES.h"
#include "./include/DESCBC.h"
#include "./include/2DESCBC.h"
#include "./include/3DESCBC.h"


char * inputString(FILE * stream, int iMaxSize);
Block takeHexInput();

void testDES() {
	Block message = initBlock(64);
	KeySchedule k1;
	Block key = (unsigned char*)"12345678";
	Block cifer;
	memset(message, 0x01, 8);
	k1 = DESKeySchedule(key);
	cifer = DESEncrypt(message, k1);
	//17 c1 2b 68 ab 3a a1 4c
}

DataChunk DESECBEncrypt(DataChunk messageChunk, Block key)
{
	DataChunk cipherChunk = initDataChunk(messageChunk.iLength - messageChunk.iLength % 8 + 16);
	Block message = initBlock(64), cipher;
	KeySchedule k;
	int i;

	cipher = initBlock(64);
	k = DESKeySchedule(key);
	for (i = 0; i < messageChunk.iLength / 8; i++) {
		memcpy(message, messageChunk.block + 8 * i, 8);
		cipher = DESEncrypt(message, k);
		memcpy(cipherChunk.block + 8 * i, cipher, 8);
	}
	free(message);

	// If the length is not an integral multiple of 8.
	if (messageChunk.iLength % 8) {
		memcpy((message = initBlock(64)), messageChunk.block + 8 * i, messageChunk.iLength % 8);
		cipher = DESEncrypt(message, k);
		memcpy(cipherChunk.block + 8 * i, cipher, 8);
	}

	return (cipherChunk);
}

void testDES_ECB() {
	DataChunk messageChunk = initDataChunk(16);
	DataChunk result;
	Block key = (unsigned char*)"12345678";
	messageChunk.block = (Block)"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D";
	messageChunk.iLength = 14;

	result = DESECBEncrypt(messageChunk, key);
}

int main(void)
{
	testDES_ECB();
// 	testDES();
	return;
// 	DataChunk messageChunk = initDataChunk(150), cipherChunk, decryptChunk;
// 	Block message = initBlock(64), cipher;
// 	Block key1, key2, IV;
// 	KeySchedule k1, k2;
// 	int i;
// 
// 	key1 = takeHexInput();
// 	key2 = takeHexInput();
// 
// 	k1 = DESKeySchedule(key1);
// 	k2 = DESKeySchedule(key2);
// 
// /*
// 	message = inputString(stdin, 150);
// 	cipher = DES3Encrypt(message, k1, k2);
// 
// 	printf("\n");
// 	for (i = 0; i < 8; i++)
// 		printf("%x ", cipher[i]);
// 	printf("\n");
// 
// 	fwrite(DES3Decrypt(cipher, k1, k2), 1, 9, stdout);
// 	printf("\n");
// */
// //
// 	messageChunk.block = inputString(stdin, 150);
// 	messageChunk.iLength = strlen(messageChunk.block) + 1;
// 
// 	cipherChunk = DESCBCEncrypt(messageChunk, key1);
// 
// 	printf("\n");
// 	for (i = 0; i < cipherChunk.iLength; i++)
// 		printf("%x ", cipherChunk.block[i]);
// 	printf("\n");
// 
// 	decryptChunk = DESCBCDecrypt(cipherChunk, key1);
// 	(decryptChunk.iLength)++;
// 
// 	printf("%s", decryptChunk.block);
// //
// 	return (0);
}


char * inputString(FILE * stream, int iMaxSize)
{
	char * szTemp;
	int iEnd;

	szTemp = (char *) malloc(iMaxSize * sizeof (char));

	do
	{
		fgets(szTemp, iMaxSize, stream);

		// Remove newline, if present.
		iEnd = strlen(szTemp) - 1;
		if (szTemp[iEnd] == '\n')
		{
			szTemp[iEnd] = '\0';
		}
	} while (strlen(szTemp) == 0);


	if (strlen(szTemp) >= iMaxSize - 1)
	{
		while (getchar() != '\n')
			;
	}

	return (szTemp);
}

Block takeHexInput()
{
	Block key = initBlock(64);
	int i;

	for (i = 0; i < 8; i++)
		scanf("%x", & key[i]);

	return (key);
}

