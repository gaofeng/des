// HEADER FILE DES.h.

#ifndef DES1
#define DES1

#include <stdlib.h>


#define initBlock(iLength) (Block) calloc((iLength) / 8, sizeof (uChar))
#define initKeySchedule (KeySchedule) malloc(16 * sizeof (uChar *))

#define isBitSet(array, bitNum) array[(bitNum) / 8] & (1 << 7 - (bitNum) % 8)
#define setBit(ch, bitPos) (ch |= 1 << 7 - (bitPos))
#define resetBit(ch, bitPos) (ch &= ~(1 << 7 - (bitPos)))


typedef unsigned char uChar;
typedef unsigned char * Block, * Table;
typedef unsigned char * * KeySchedule;


extern uChar PC1[];
extern uChar PC2[];
extern uChar E[];
extern uChar S[][][];
extern uChar P[];
extern uChar IP[];
extern uChar IPInv[];


Block blockXOR(Block arg1, Block arg2, int iSize);
Block blockConcatenate(Block a, Block b);
void blockLeftRotateHalves(Block cd);

Block blockPermute(Table table, Block input, int iOutputSize);
Block blockPermuteSBox(Block input);

Block f(Block a, Block subKey);
KeySchedule DESKeySchedule(Block key);
Block DESEncrypt(Block message, KeySchedule k);
Block DESDecrypt(Block cipher, KeySchedule k);


#endif
