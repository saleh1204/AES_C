#ifndef AES_HELPER_H
#define AES_HELPER_H
#include <stdint.h>
#include <stdio.h>
// Encryption Functions
void subBytes(uint8_t inByte, uint8_t *outByte);

void subWord(uint8_t *inWord, uint8_t *outWord);

void shiftRows(uint8_t *inWord0, uint8_t *inWord1, uint8_t *inWord2,
               uint8_t *inWord3, uint8_t *outWord0, uint8_t *outWord1,
               uint8_t *outWord2, uint8_t *outWord3);

void mixColumns(uint8_t *inWord0, uint8_t *inWord1, uint8_t *inWord2,
                uint8_t *inWord3, uint8_t *outWord0, uint8_t *outWord1,
                uint8_t *outWord2, uint8_t *outWord3);

// Decryption Functions
void invSubBytes(uint8_t inByte, uint8_t *outByte);

void invSubWord(uint8_t *inWord, uint8_t *outWord);

void invShiftRows(uint8_t *inWord0, uint8_t *inWord1, uint8_t *inWord2,
                  uint8_t *inWord3, uint8_t *outWord0, uint8_t *outWord1,
                  uint8_t *outWord2, uint8_t *outWord3);

void invMixColumns(uint8_t *inWord0, uint8_t *inWord1, uint8_t *inWord2,
                   uint8_t *inWord3, uint8_t *outWord0, uint8_t *outWord1,
                   uint8_t *outWord2, uint8_t *outWord3);

// Common Function
void printVector(char *msg, uint8_t *vector, size_t len);

void addRoundKey(uint8_t *inWord0, uint8_t *inWord1, uint8_t *inWord2,
                 uint8_t *inWord3, uint8_t *inKey0, uint8_t *inKey1,
                 uint8_t *inKey2, uint8_t *inKey3, uint8_t *outWord0,
                 uint8_t *outWord1, uint8_t *outWord2, uint8_t *outWord3);
void keyExpansion(uint8_t *inKey0, uint8_t *inKey1, uint8_t *inKey2,
                  uint8_t *inKey3, uint8_t roundNo, uint8_t *outKey0,
                  uint8_t *outKey1, uint8_t *outKey2, uint8_t *outKey3);
#endif