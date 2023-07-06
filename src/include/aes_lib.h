#ifndef AES_LIB_H
#define AES_LIB_H
#include "aes_helper.h"

void aesInitKeys(uint8_t *initialKey, uint8_t verbose);

void aesEncrypt(uint8_t *plainText, uint8_t *cipherText, uint8_t verbose);

void aesDecrypt(uint8_t *cipherText, uint8_t *plainText, uint8_t verbose);

#endif