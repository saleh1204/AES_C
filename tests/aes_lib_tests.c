#include <aes_lib.h>
#include "munit.h"

// AES Encryption tests
static MunitResult aesEncryptionTests(const MunitParameter params[],
                                      void *fixture) {
  // Test #1
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
  // Control verbosity of the AES library calls
  uint8_t verbose = 0;
  // Initialize keys for all rounds
  aesInitKeys(key, verbose);
  // Encrypt given plain text with pre-initialized keys
  aesEncrypt((uint8_t *)&plainText, (uint8_t *)&cipherText, verbose);
  munit_assert_memory_equal(16, cipherText, expectedCipher);

  // if all tests passed, return ok
  return MUNIT_OK;
}

// AES Decryption tests
static MunitResult aesDecryptionTests(const MunitParameter params[],
                                      void *fixture) {
  // Test #1
  // array to hold a predefined cipher text to be decrypted
  uint8_t cipher[16] = {0x69, 0xC4, 0xE0, 0xD8, 0x6A, 0x7B, 0x04, 0x30,
                        0xD8, 0xCD, 0xB7, 0x80, 0x70, 0xB4, 0xC5, 0x5A};
  // Initial key to be used for initialize the remaining keys (key expansion)
  uint8_t key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
  // array to hold the generated plain text
  uint8_t decrpted[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  // Expected Plain text output
  uint8_t expectedPlainText[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55,
                                   0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb,
                                   0xcc, 0xdd, 0xee, 0xff};
  // Control verbosity of the AES library calls
  uint8_t verbose = 0;
  // Initialize keys for all rounds
  aesInitKeys(key, verbose);
  // Decrypt given cipher text with pre-initialized keys
  aesDecrypt((uint8_t *)&cipher, (uint8_t *)&decrpted, verbose);
  munit_assert_memory_equal(16, decrpted, expectedPlainText);
  // if all tests passed, return ok
  return MUNIT_OK;
}

static MunitTest aes_lib_tests[] = {
    {
        "AES Encryption",       /* name */
        aesEncryptionTests,     /* test */
        NULL,                   /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "AES Decryption",       /* name */
        aesDecryptionTests,     /* test */
        NULL,                   /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    /* Mark the end of the array with an entry where the test
     * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */
static const MunitSuite test_suite = {
    /* This string will be prepended to all test names in this suite;
     * for example, "/example/rand" will become "/µnit/example/rand".
     * Note that, while it doesn't really matter for the top-level
     * suite, NULL signal the end of an array of tests; you should use
     * an empty string ("") instead. */
    (char *)"",
    /* The first parameter is the array of test suites. */
    aes_lib_tests,
    /* In addition to containing test cases, suites can contain other
     * test suites.  This isn't necessary in this example, but it can be
     * a great help to projects with lots of tests by making it easier
     * to spread the tests across many files.  This is where you would
     * put "other_suites" (which is commented out above). */
    NULL,
    /* An interesting feature of µnit is that it supports automatically
     * running multiple iterations of the tests.  This is usually only
     * interesting if you make use of the PRNG to randomize your tests
     * cases a bit, or if you are doing performance testing and want to
     * average multiple runs.  0 is an alias for 1. */
    1,
    /* Just like MUNIT_TEST_OPTION_NONE, you can provide
     * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
    MUNIT_SUITE_OPTION_NONE};
int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  printf("AES Library Functions Tests\n");
  // Runnin unit tests for aes helper library
  return munit_suite_main(&test_suite, (void *)"aes_lib tests", argc, argv);
}
