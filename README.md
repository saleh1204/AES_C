AES Implementation in C Programming Language
===========================

## What Is This?
------------
This is a simple and basic implementation of AES Cryptographic algorithm in C Programming Language. This implements Electronic codebook (ECB) mode of AES, where each data block is encrypted/decrypted separately. Other modes can be used on top of this library. It is highly portable where it does not require external libraries or dynamic memory allocation (i.e. malloc) which makes it perfect for embedded systems and light weight applications. It does not depend on any external library for compiling the sources. It only requires `<stdint.h>` for `uint8_t` data type and `<stdio.h>` for verbose output (i.e. `printf`) of the encryption/decryption stages.  

## How to build this project?
------------
This project utilizes **CMake** for building the project. Steps for building and testing the application is shown below. You can add the following option to cmake command `-D BUILD_TESTS=ON` to compile the unit tests for AES library. 

``` bash
mkdir build
cd build 
cmake ../
make run  # to run sample application
make test # to test AES library
```

## Basic Usage of the library
------------
Sample Usage of the AES library is shown below and in the `aes_main.c` file. Before encrypting or decrypting data, the keys need to initialized using `aesInitKeys(uint8_t *initial_key, uint8_t verbose)` function. Afterwards, plain texts can be encrypted using `aesEncrypt(uint8_t *plain_text, uint8_t *cipher_text)` function, or cipher texts can be decrypted using `aesEncrypt(uint8_t *plain_text, uint8_t *cipher_text)` function.

``` c
#include "include/aes_lib.h"

int main(int argc, char **argv)
{
  printf("\033[0;32m----------------------AES Main Program----------------------\033[0;37m\n\n");
  // Initial plain text to be encrypted
  uint8_t plainText[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                           0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
  // Initial key to be used for initialize the remaining keys (key expansion)
  uint8_t key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
  // array to hold the generated cipher text
  uint8_t cipherText[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  // array to hold a predefined cipher text to be decrypted
  uint8_t expectedCipher[16] = {0x69, 0xC4, 0xE0, 0xD8, 0x6A, 0x7B, 0x04, 0x30,
                                0xD8, 0xCD, 0xB7, 0x80, 0x70, 0xB4, 0xC5, 0x5A};
  // array to hold the generated plain text
  uint8_t decrpted[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  // Control verbosity of the AES library calls
  uint8_t verbose = 0;
  // Initialize keys for all rounds
  aesInitKeys(key, verbose);
  // Encrypt given plain text with pre-initialized keys
  aesEncrypt((uint8_t *)&plainText, (uint8_t *)&cipherText, verbose);
  printVector("\nciphertext   ", cipherText, 16);
  printVector("expected     ", expectedCipher, 16);
  // Decrypt given cipher text with pre-initialized keys
  aesDecrypt((uint8_t *)&cipherText, (uint8_t *)&decrpted, verbose);
  printVector("\ndecrypted    ", decrpted, 16);
  printVector("expected     ", plainText, 16);
  printf("\033[0;32m--------------------------- Done ---------------------------\033[0;37m\n\n");
  return 0;
}

```

## Project Organization
------------
    ├── src             <- folder containing source and include files
    ├── tests           <- folder contianing test cases for the AES library/application
    ├── CMakeLists.txt  <- file used by cmake for building the application
    └── README.md       <- This readme document