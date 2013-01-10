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

int main(void)
{
	DataChunk messageChunk = initDataChunk(150), cipherChunk, decryptChunk;
	Block message = initBlock(64), cipher;
	Block key1, key2, IV;
	KeySchedule k1, k2;
	int i;

	key1 = takeHexInput();
	key2 = takeHexInput();

	k1 = DESKeySchedule(key1);
	k2 = DESKeySchedule(key2);

/*
	message = inputString(stdin, 150);
	cipher = DES3Encrypt(message, k1, k2);

	printf("\n");
	for (i = 0; i < 8; i++)
		printf("%x ", cipher[i]);
	printf("\n");

	fwrite(DES3Decrypt(cipher, k1, k2), 1, 9, stdout);
	printf("\n");
*/
//
	messageChunk.block = inputString(stdin, 150);
	messageChunk.iLength = strlen(messageChunk.block) + 1;

	cipherChunk = DESCBCEncrypt(messageChunk, key1);

	printf("\n");
	for (i = 0; i < cipherChunk.iLength; i++)
		printf("%x ", cipherChunk.block[i]);
	printf("\n");

	decryptChunk = DESCBCDecrypt(cipherChunk, key1);
	(decryptChunk.iLength)++;

	printf("%s", decryptChunk.block);
//
	return (0);
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

