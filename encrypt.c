// ENCRYPTION ROUTINE.

#include <stdio.h>
#include <string.h>
#include "./include/DES.h"
#include "./include/2DES.h"
#include "./include/3DES.h"
#include "./include/DESCBC.h"
#include "./include/2DESCBC.h"
#include "./include/3DESCBC.h"


char * inputString(FILE * stream, int iMaxSize);

int main(void)
{
	DataChunk messageChunk = initDataChunk(200), cipherChunk, decryptChunk;
	Block key1 = initBlock(80), key2 = initBlock(80);

	fread(key1, 1, 8, stdin);
	fread(key2, 1, 8, stdin);

	fgets(messageChunk.block, 200, stdin); = inputString(stdin, 150);
	messageChunk.iLength = strlen(messageChunk.block) + 1;

	cipherChunk = DESCBC3Encrypt(messageChunk, key1, key2);

	decryptChunk = DESCBC3Decrypt(cipherChunk, key1, key2);
	(decryptChunk.iLength)++;

	printf("%s", decryptChunk.block);

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


