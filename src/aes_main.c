#include <aes_lib.h>

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
