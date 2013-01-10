// SOURCE FILE CONTAINING DES ROUTINES.

#include "DES.h"


uChar PC1[56] = { 57, 49, 41, 33, 25, 17,  9,
		   1, 58, 50, 42, 34, 26, 18,
		  10,  2, 59, 51, 43, 35, 27,
		  19, 11,  3, 60, 52, 44, 36,
		  63, 55, 47, 39, 31, 23, 15,
		   7, 62, 54, 46, 38, 30, 22,
		  14,  6, 61, 53, 45, 37, 29,
		  21, 13,  5, 28, 20, 12,  4 };

uChar PC2[48] = { 14, 17, 11, 24,  1,  5,
		   3, 28, 15,  6, 21, 10,
		  23, 19, 12,  4, 26,  8,
		  16,  7, 27, 20, 13,  2,
		  41, 52, 31, 37, 47, 55,
		  30, 40, 51, 45, 33, 48,
		  44, 49, 39, 56, 34, 53,
		  46, 42, 50, 36, 29, 32 };

uChar E[48] =   { 32,  1,  2,  3,  4,  5,
		   4,  5,  6,  7,  8,  9,
		   8,  9, 10, 11, 12, 13,
		  12, 13, 14, 15, 16, 17,
		  16, 17, 18, 19, 20, 21,
		  20, 21, 22, 23, 24, 25,
		  24, 25, 26, 27, 28, 29,
		  28, 29, 30, 31, 32,  1 };

uChar S[8][4][16] = {
		      {					// S1.
			{ 14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
			{  0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
			{  4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
			{ 15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
		      },
		      {					// S2.
			{ 15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
			{  3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
			{  0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
			{ 13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}
		      },
		      {					// S3.
			{ 10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
			{ 13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
			{ 13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
			{  1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
		      },
		      {					// S4.
			{  7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
			{ 13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
			{ 10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
			{  3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
		      },
		      {					// S5.
			{  2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
			{ 14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
			{  4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
			{ 11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}
		      },
		      {					// S6.
			{ 12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
			{ 10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
			{  9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
			{  4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}
		      },
		      {					// S7.
			{  4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
			{ 13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
			{  1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
			{  6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}
		      },
		      {					// S8.
			{ 13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
			{  1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
			{  7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
			{  2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
		      }
		    };

uChar P[32] = 	{ 16,  7, 20, 21,
		  29, 12, 28, 17,
		   1, 15, 23, 26,
		   5, 18, 31, 10,
		   2,  8, 24, 14,
		  32, 27,  3,  9,
		  19, 13, 30,  6,
		  22, 11,  4, 25 };

uChar IP[64] = 	  { 58, 50, 42, 34, 26, 18, 10,  2,
		    60, 52, 44, 36, 28, 20, 12,  4,
		    62, 54, 46, 38, 30, 22, 14,  6,
		    64, 56, 48, 40, 32, 24, 16,  8,
		    57, 49, 41, 33, 25, 17,  9,  1,
		    59, 51, 43, 35, 27, 19, 11,  3,
		    61, 53, 45, 37, 29, 21, 13,  5,
		    63, 55, 47, 39, 31, 23, 15,  7 };

uChar IPInv[64] = { 40,  8,  48,  16,  56,  24,  64,  32,
		    39,  7,  47,  15,  55,  23,  63,  31,
		    38,  6,  46,  14,  54,  22,  62,  30,
		    37,  5,  45,  13,  53,  21,  61,  29,
		    36,  4,  44,  12,  52,  20,  60,  28,
		    35,  3,  43,  11,  51,  19,  59,  27,
		    34,  2,  42,  10,  50,  18,  58,  26,
		    33,  1,  41,   9,  49,  17,  57,  25 };


Block blockXOR(Block arg1, Block arg2, int iSize)
{
	int i;

	for (i = 0; i < iSize / 8; i++)
		arg1[i] ^= arg2[i];

	return (arg1);
}


Block blockConcatenate(Block a, Block b)
{
	Block output = initBlock(64);
	int i;

	for (i = 0; i < 4; i++) {
		output[i] = a[i];
		output[i + 4] = b[i];
	}

	return (output);
}


void blockLeftRotateHalves(Block cd)
{
	uChar bTest;
	int i;

	bTest = cd[0] & 0x80;	// Get the MSB.

	for (i = 0; i < 6; i++)	// Left shift the entire array.
		cd[i] = (cd[i] << 1) | ((cd[i+1] & 0x80) >> 7);

	cd[6] = (cd[6] << 1) | ((cd[3] & 0x10) >> 4);
	bTest ? setBit(cd[3], 3) : resetBit(cd[3], 3);
}


Block blockPermute(Table table, Block input, int iOutputSize)
{
	Block output = initBlock(iOutputSize);
	int iTableSize = iOutputSize;
	int i;

	for (i = 0; i < iTableSize ; i++)
		if (isBitSet(input, table[i] - 1))
			setBit(output[i / 8], i % 8);

	return (output);
}


Block blockPermuteSBox(Block input)
{
	Block result = initBlock(32);
	uChar row = 0, column = 0;
	int i;

	for (i = 0; i < 8; i++, row = column = 0) {
		if (isBitSet(input, 6 * i))
			setBit(row, 6);
		if (isBitSet(input, 6 * i + 5))
			setBit(row, 7);

		if (isBitSet(input, 6 * i + 1))
			setBit(column, 4);
		if (isBitSet(input, 6 * i + 2))
			setBit(column, 5);
		if (isBitSet(input, 6 * i + 3))
			setBit(column, 6);
		if (isBitSet(input, 6 * i + 4))
			setBit(column, 7);

		result[i / 2] |= S[i][row][column] << (i % 2 ? 0 : 4);
	}

	return (result);
}


Block f(Block a, Block subKey)
{
	return (blockPermute(P, blockPermuteSBox(blockXOR(blockPermute(E, a, 48), subKey, 48)), 32));
}


KeySchedule DESKeySchedule(Block key)
{
	KeySchedule keySchedule = initKeySchedule; 	// 16 sub-keys of 48 bits each.
	Block CiDi;
	int i;

	CiDi = blockPermute(PC1, key, 56);

	for (i = 0; i < 16; i++) {
		blockLeftRotateHalves(CiDi);
		if (i != 0 && i != 1 && i != 8 && i != 15)
			blockLeftRotateHalves(CiDi);

		keySchedule[i] = blockPermute(PC2, CiDi, 48);
	}

	return (keySchedule);
}


Block DESEncrypt(Block message, KeySchedule k)
{
	Block L, R, Lprev, Rprev;
	int i;

	Lprev = L = blockPermute(IP, message, 64);
	Rprev = R = & L[4];

	for (i = 0; i < 16; i++, Lprev = L, Rprev = R) {
		L = Rprev;
		R = blockXOR(Lprev, f(Rprev, k[i]), 32);
	}

	return (blockPermute(IPInv, blockConcatenate(R, L), 64));
}


Block DESDecrypt(Block cipher, KeySchedule k)
{
	Block L, R, Lprev, Rprev;
	int i;

	Lprev = L = blockPermute(IP, cipher, 64);
	Rprev = R = & L[4];

	for (i = 0; i < 16; i++, Lprev = L, Rprev = R) {
		L = Rprev;
		R = blockXOR(Lprev, f(Rprev, k[15 - i]), 32);
	}

	return (blockPermute(IPInv, blockConcatenate(R, L), 64));
}

