#include <aes_lib.h>

static uint8_t keys[11][16];
// Implementation of AES Key Expansion for all keys
void aesInitKeys(uint8_t *initialKey, uint8_t verbose)
{
  if (verbose == 1)
  {
    printf("\033[0;34m----------------------- Key Expansion ----------------------\033[0;37m\n");
  }
  for (uint8_t i = 0; i < 16; i++)
  {
    keys[0][i] = initialKey[i];
  }
  if (verbose == 1)
  {
    printVector("keys[0]      ", keys[0], 16);
  }
  for (uint8_t i = 0; i <= 9; i++)
  {
    keyExpansion((uint8_t *) (&keys[i][0]), (uint8_t *) (&keys[i][4]), (uint8_t *) (&keys[i][8]),
                 (uint8_t *) (&keys[i][12]), i, (uint8_t *) (&keys[i + 1][0]),
                 (uint8_t *) (&keys[i + 1][4]), (uint8_t *) (&keys[i + 1][8]),
                 (uint8_t *) (&keys[i + 1][12]));
    if (verbose == 1)
    {
      printf("keys[%x]      ", i + 1);
      printVector("", keys[i + 1], 16);
    }
  }
}

// Implementation of AES Encrption function after the keys have been initialized
void aesEncrypt(uint8_t *plainText, uint8_t *cipherText, uint8_t verbose)
{
  if (verbose == 1)
  {
    printf("\033[0;34m------------------------ Encryption ------------------------\033[0;37m\n");
  }
  uint8_t plainTextTemp[16];
  // Copying the input text to temproary variable
  for (uint8_t i = 0; i < 16; i++)
  {
    plainTextTemp[i] = plainText[i];
  }
  if (verbose == 1)
  {
    printVector("round[0].in  ", plainTextTemp, 16);
    printVector("round[0].k   ", keys[0], 16);
  }
  // Pre-Rounds (Round 0)
  addRoundKey((uint8_t *) (&plainTextTemp[0]), (uint8_t *) (&plainTextTemp[4]),
              (uint8_t *) (&plainTextTemp[8]), (uint8_t *) (&plainTextTemp[12]),
              (uint8_t *) (&keys[0][0]), (uint8_t *) (&keys[0][4]), (uint8_t *) (&keys[0][8]),
              (uint8_t *) (&keys[0][12]), (uint8_t *) (&plainTextTemp[0]),
              (uint8_t *) (&plainTextTemp[4]), (uint8_t *) (&plainTextTemp[8]),
              (uint8_t *) (&plainTextTemp[12]));

  // Rounds 1 to 10
  for (uint8_t i = 1; i <= 10; i++)
  {
    if (verbose == 1)
    {
      printf("\nround[%x]", i);
      printVector(".in  ", plainTextTemp, 16);
    }
    // First stage: SubBytes
    subWord((uint8_t *) (&plainTextTemp[0]), (uint8_t *) (&plainTextTemp[0]));
    subWord((uint8_t *) (&plainTextTemp[4]), (uint8_t *) (&plainTextTemp[4]));
    subWord((uint8_t *) (&plainTextTemp[8]), (uint8_t *) (&plainTextTemp[8]));
    subWord((uint8_t *) (&plainTextTemp[12]), (uint8_t *) (&plainTextTemp[12]));
    if (verbose == 1)
    {
      printf("round[%x]", i);
      printVector(".sb  ", plainTextTemp, 16);
    }
    // Second Stage: shiftRows
    shiftRows((uint8_t *) (&plainTextTemp[0]), (uint8_t *) (&plainTextTemp[4]),
              (uint8_t *) (&plainTextTemp[8]), (uint8_t *) (&plainTextTemp[12]),
              (uint8_t *) (&plainTextTemp[0]), (uint8_t *) (&plainTextTemp[4]),
              (uint8_t *) (&plainTextTemp[8]), (uint8_t *) (&plainTextTemp[12]));
    if (verbose == 1)
    {
      printf("round[%x]", i);
      printVector(".sr  ", plainTextTemp, 16);
    }
    // Third Stage: Mix Column only if it is not the last round
    if (i != 10)
    {
      mixColumns((uint8_t *) (&plainTextTemp[0]), (uint8_t *) (&plainTextTemp[4]),
                 (uint8_t *) (&plainTextTemp[8]), (uint8_t *) (&plainTextTemp[12]),
                 (uint8_t *) (&plainTextTemp[0]), (uint8_t *) (&plainTextTemp[4]),
                 (uint8_t *) (&plainTextTemp[8]), (uint8_t *) (&plainTextTemp[12]));
      if (verbose == 1)
      {
        printf("round[%x]", i);
        printVector(".mc  ", plainTextTemp, 16);
      }
    }
    // Fourth Stage: addRoundKey
    if (verbose == 1)
    {
      printf("round[%x]", i);
      printVector(".k   ", keys[i], 16);
    }
    addRoundKey((uint8_t *) (&plainTextTemp[0]), (uint8_t *) (&plainTextTemp[4]),
                (uint8_t *) (&plainTextTemp[8]), (uint8_t *) (&plainTextTemp[12]),
                (uint8_t *) (&keys[i][0]), (uint8_t *) (&keys[i][4]), (uint8_t *) (&keys[i][8]),
                (uint8_t *) (&keys[i][12]), (uint8_t *) (&plainTextTemp[0]),
                (uint8_t *) (&plainTextTemp[4]), (uint8_t *) (&plainTextTemp[8]),
                (uint8_t *) (&plainTextTemp[12]));
  }
  // Copying the output encrypted text to cipher variable
  for (uint8_t i = 0; i < 16; i++)
  {
    cipherText[i] = plainTextTemp[i];
  }
}

// Implementation of AES Decryption function after the keys have been initialized
void aesDecrypt(uint8_t *cipherText, uint8_t *plainText, uint8_t verbose)
{
  if (verbose == 1)
  {
    printf("\033[0;34m------------------------ Decryption ------------------------\033[0;37m\n");
  }
  uint8_t cipherTextTemp[16];
  // Copying the input text to temproary variable
  for (uint8_t i = 0; i < 16; i++)
  {
    cipherTextTemp[i] = cipherText[i];
  }
  if (verbose == 1)
  {
    printf("\nround[%x]", 0);
    printVector(".in  ", cipherTextTemp, 16);
    printf("round[%x]", 0);
    printVector(".k   ", keys[10], 16);
  }
  // Pre-Rounds (Round 0)
  addRoundKey((uint8_t *) (&cipherTextTemp[0]), (uint8_t *) (&cipherTextTemp[4]),
              (uint8_t *) (&cipherTextTemp[8]), (uint8_t *) (&cipherTextTemp[12]),
              (uint8_t *) (&keys[10][0]), (uint8_t *) (&keys[10][4]), (uint8_t *) (&keys[10][8]),
              (uint8_t *) (&keys[10][12]), (uint8_t *) (&cipherTextTemp[0]),
              (uint8_t *) (&cipherTextTemp[4]), (uint8_t *) (&cipherTextTemp[8]),
              (uint8_t *) (&cipherTextTemp[12]));

  // Rounds 1 to 10
  for (uint8_t i = 1; i <= 10; i++)
  {
    if (verbose == 1)
    {
      printf("\nround[%x]", i);
      printVector(".in  ", cipherTextTemp, 16);
    }
    // First Stage: invShiftRows
    invShiftRows((uint8_t *) (&cipherTextTemp[0]), (uint8_t *) (&cipherTextTemp[4]),
                 (uint8_t *) (&cipherTextTemp[8]), (uint8_t *) (&cipherTextTemp[12]),
                 (uint8_t *) (&cipherTextTemp[0]), (uint8_t *) (&cipherTextTemp[4]),
                 (uint8_t *) (&cipherTextTemp[8]), (uint8_t *) (&cipherTextTemp[12]));
    if (verbose == 1)
    {
      printf("round[%x]", i);
      printVector(".isr ", cipherTextTemp, 16);
    }

    // Second stage: InvSubBytes
    invSubWord((uint8_t *) (&cipherTextTemp[0]), (uint8_t *) (&cipherTextTemp[0]));
    invSubWord((uint8_t *) (&cipherTextTemp[4]), (uint8_t *) (&cipherTextTemp[4]));
    invSubWord((uint8_t *) (&cipherTextTemp[8]), (uint8_t *) (&cipherTextTemp[8]));
    invSubWord((uint8_t *) (&cipherTextTemp[12]), (uint8_t *) (&cipherTextTemp[12]));
    if (verbose == 1)
    {
      printf("round[%x]", i);
      printVector(".isb ", cipherTextTemp, 16);
    }

    // Third Stage: addRoundKey
    if (verbose == 1)
    {
      printf("round[%x]", i);
      printVector(".k   ", keys[10 - i], 16);
    }
    addRoundKey((uint8_t *) (&cipherTextTemp[0]), (uint8_t *) (&cipherTextTemp[4]),
                (uint8_t *) (&cipherTextTemp[8]), (uint8_t *) (&cipherTextTemp[12]),
                (uint8_t *) (&keys[10 - i][0]), (uint8_t *) (&keys[10 - i][4]),
                (uint8_t *) (&keys[10 - i][8]), (uint8_t *) (&keys[10 - i][12]),
                (uint8_t *) (&cipherTextTemp[0]), (uint8_t *) (&cipherTextTemp[4]),
                (uint8_t *) (&cipherTextTemp[8]), (uint8_t *) (&cipherTextTemp[12]));
    if (verbose == 1)
    {
      printf("round[%x]", i);
      printVector(".adk ", cipherTextTemp, 16);
    }
    // Fourth Stage: Inverse Mix Column only if it is not the last round
    if (i != 10)
    {
      invMixColumns((uint8_t *) (&cipherTextTemp[0]), (uint8_t *) (&cipherTextTemp[4]),
                    (uint8_t *) (&cipherTextTemp[8]), (uint8_t *) (&cipherTextTemp[12]),
                    (uint8_t *) (&cipherTextTemp[0]), (uint8_t *) (&cipherTextTemp[4]),
                    (uint8_t *) (&cipherTextTemp[8]), (uint8_t *) (&cipherTextTemp[12]));
      if (verbose == 1)
      {
        printf("round[%x]", i);
        printVector(".imc ", cipherTextTemp, 16);
      }
    }
  }
  // Copying the output encrypted text to cipher variable
  for (uint8_t i = 0; i < 16; i++)
  {
    plainText[i] = cipherTextTemp[i];
  }
}