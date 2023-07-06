
#include <stdio.h>
#include "munit.h"
#include "../src/include/aes_helper.h"

// SubBytes Tests
static MunitResult subBytesTests(const MunitParameter params[], void *fixture)
{
  uint8_t result;
  // Test #1
  subBytes(0x53, &result);
  munit_assert_uint8(result, ==, 0xED);

  // Test #2
  subBytes(0x00, &result);
  munit_assert_uint8(result, ==, 0x63);

  // Test #3
  subBytes(0x34, &result);
  munit_assert_uint8(result, ==, 0x18);

  // Test #4
  subBytes(0x40, &result);
  munit_assert_uint8(result, ==, 0x09);

  // if all tests passed, return ok
  return MUNIT_OK;
}

// Shift Rows tests
static MunitResult shiftRowsTests(const MunitParameter params[], void *fixture)
{
  // Test #1
  // input 63 CA B7 04 09 53 D0 51 CD 60 E0 E7 BA 70 E1 8C
  uint8_t input1[4] = {0x63, 0xCA, 0xB7, 0x04};
  uint8_t input2[4] = {0x09, 0x53, 0xD0, 0x51};
  uint8_t input3[4] = {0xCD, 0x60, 0xE0, 0xE7};
  uint8_t input4[4] = {0xBA, 0x70, 0xE1, 0x8C};
  uint8_t result1[4], result2[4], result3[4], result4[4];
  // expected result 63 53 E0 8C 09 60 E1 04 CD 70 B7 51 BA CA D0 E7
  uint8_t expected1[4] = {0x63, 0x53, 0xE0, 0x8C};
  uint8_t expected2[4] = {0x09, 0x60, 0xE1, 0x04};
  uint8_t expected3[4] = {0xCD, 0x70, 0xB7, 0x51};
  uint8_t expected4[4] = {0xBA, 0xCA, 0xD0, 0xE7};
  shiftRows((uint8_t *)input1, (uint8_t *)input2, (uint8_t *)input3, (uint8_t *)input4,
            (uint8_t *)result1, (uint8_t *)result2, (uint8_t *)result3, (uint8_t *)result4);
  munit_assert_memory_equal(4, result1, expected1);
  munit_assert_memory_equal(4, result2, expected2);
  munit_assert_memory_equal(4, result3, expected3);
  munit_assert_memory_equal(4, result4, expected4);

  // Test #2
  // input A7 61 CA 9B 97 BE 8B 45 D8 AD 1A 61 1F C9 73 69
  input1[0] = 0xA7;
  input1[1] = 0x61;
  input1[2] = 0xCA;
  input1[3] = 0x9B;

  input2[0] = 0x97;
  input2[1] = 0xBE;
  input2[2] = 0x8B;
  input2[3] = 0x45;

  input3[0] = 0xD8;
  input3[1] = 0xAD;
  input3[2] = 0x1A;
  input3[3] = 0x61;

  input4[0] = 0x1F;
  input4[1] = 0xC9;
  input4[2] = 0x73;
  input4[3] = 0x69;

  // expected result A7 BE 1A 69 97 AD 73 9B D8 C9 CA 45 1F 61 8B 61
  expected1[0] = 0xA7;
  expected1[1] = 0xBE;
  expected1[2] = 0x1A;
  expected1[3] = 0x69;

  expected2[0] = 0x97;
  expected2[1] = 0xAD;
  expected2[2] = 0x73;
  expected2[3] = 0x9B;

  expected3[0] = 0xD8;
  expected3[1] = 0xC9;
  expected3[2] = 0xCA;
  expected3[3] = 0x45;

  expected4[0] = 0x1F;
  expected4[1] = 0x61;
  expected4[2] = 0x8B;
  expected4[3] = 0x61;

  shiftRows((uint8_t *)input1, (uint8_t *)input2, (uint8_t *)input3, (uint8_t *)input4,
            (uint8_t *)result1, (uint8_t *)result2, (uint8_t *)result3, (uint8_t *)result4);
  munit_assert_memory_equal(4, result1, expected1);
  munit_assert_memory_equal(4, result2, expected2);
  munit_assert_memory_equal(4, result3, expected3);
  munit_assert_memory_equal(4, result4, expected4);

  // Test #3
  // input 3B 59 CB 73 FC D9 0E E0 57 74 22 2D C0 67 FB 68
  input1[0] = 0x3B;
  input1[1] = 0x59;
  input1[2] = 0xCB;
  input1[3] = 0x73;

  input2[0] = 0xFC;
  input2[1] = 0xD9;
  input2[2] = 0x0E;
  input2[3] = 0xE0;

  input3[0] = 0x57;
  input3[1] = 0x74;
  input3[2] = 0x22;
  input3[3] = 0x2D;

  input4[0] = 0xC0;
  input4[1] = 0x67;
  input4[2] = 0xFB;
  input4[3] = 0x68;

  // expected result 3B D9 22 68 FC 74 FB 73 57 67 CB E0 C0 59 0E 2D
  expected1[0] = 0x3B;
  expected1[1] = 0xD9;
  expected1[2] = 0x22;
  expected1[3] = 0x68;

  expected2[0] = 0xFC;
  expected2[1] = 0x74;
  expected2[2] = 0xFB;
  expected2[3] = 0x73;

  expected3[0] = 0x57;
  expected3[1] = 0x67;
  expected3[2] = 0xCB;
  expected3[3] = 0xE0;

  expected4[0] = 0xC0;
  expected4[1] = 0x59;
  expected4[2] = 0x0E;
  expected4[3] = 0x2D;

  shiftRows((uint8_t *)input1, (uint8_t *)input2, (uint8_t *)input3, (uint8_t *)input4,
            (uint8_t *)result1, (uint8_t *)result2, (uint8_t *)result3, (uint8_t *)result4);
  munit_assert_memory_equal(4, result1, expected1);
  munit_assert_memory_equal(4, result2, expected2);
  munit_assert_memory_equal(4, result3, expected3);
  munit_assert_memory_equal(4, result4, expected4);

  // if all tests passed, return ok
  return MUNIT_OK;
}

// Mix Columns tests
static MunitResult mixColumnsTests(const MunitParameter params[], void *fixture)
{
  // Test #1
  // input 63 53 E0 8C 09 60 E1 04 CD 70 B7 51 BA CA D0 E7
  uint8_t input1[4] = {0x63, 0x53, 0xE0, 0x8C};
  uint8_t input2[4] = {0x09, 0x60, 0xE1, 0x04};
  uint8_t input3[4] = {0xCD, 0x70, 0xB7, 0x51};
  uint8_t input4[4] = {0xBA, 0xCA, 0xD0, 0xE7};
  uint8_t result1[4], result2[4], result3[4], result4[4];
  // expected result 5F 72 64 15 57 F5 BC 92 F7 BE 3B 29 1D B9 F9 1A
  uint8_t expected1[4] = {0x5F, 0x72, 0x64, 0x15};
  uint8_t expected2[4] = {0x57, 0xF5, 0xBC, 0x92};
  uint8_t expected3[4] = {0xF7, 0xBE, 0x3B, 0x29};
  uint8_t expected4[4] = {0x1D, 0xB9, 0xF9, 0x1A};
  mixColumns((uint8_t *)input1, (uint8_t *)input2, (uint8_t *)input3, (uint8_t *)input4,
             (uint8_t *)result1, (uint8_t *)result2, (uint8_t *)result3, (uint8_t *)result4);
  munit_assert_memory_equal(4, result1, expected1);
  munit_assert_memory_equal(4, result2, expected2);
  munit_assert_memory_equal(4, result3, expected3);
  munit_assert_memory_equal(4, result4, expected4);

  // Test #2
  // input A7 BE 1A 69 97 AD 73 9B D8 C9 CA 45 1F 61 8B 61
  input1[0] = 0xA7;
  input1[1] = 0xBE;
  input1[2] = 0x1A;
  input1[3] = 0x69;

  input2[0] = 0x97;
  input2[1] = 0xAD;
  input2[2] = 0x73;
  input2[3] = 0x9B;

  input3[0] = 0xD8;
  input3[1] = 0xC9;
  input3[2] = 0xCA;
  input3[3] = 0x45;

  input4[0] = 0x1F;
  input4[1] = 0x61;
  input4[2] = 0x8B;
  input4[3] = 0x61;

  // expected result FF 87 96 84 31 D8 6A 51 64 51 51 FA 77 3A D0 09
  expected1[0] = 0xFF;
  expected1[1] = 0x87;
  expected1[2] = 0x96;
  expected1[3] = 0x84;

  expected2[0] = 0x31;
  expected2[1] = 0xD8;
  expected2[2] = 0x6A;
  expected2[3] = 0x51;

  expected3[0] = 0x64;
  expected3[1] = 0x51;
  expected3[2] = 0x51;
  expected3[3] = 0xFA;

  expected4[0] = 0x77;
  expected4[1] = 0x3A;
  expected4[2] = 0xD0;
  expected4[3] = 0x09;

  mixColumns((uint8_t *)input1, (uint8_t *)input2, (uint8_t *)input3, (uint8_t *)input4,
            (uint8_t *)result1, (uint8_t *)result2, (uint8_t *)result3, (uint8_t *)result4);
  munit_assert_memory_equal(4, result1, expected1);
  munit_assert_memory_equal(4, result2, expected2);
  munit_assert_memory_equal(4, result3, expected3);
  munit_assert_memory_equal(4, result4, expected4);

  // Test #3
  // input 3B D9 22 68 FC 74 FB 73 57 67 CB E0 C0 59 0E 2D
  input1[0] = 0x3B;
  input1[1] = 0xD9;
  input1[2] = 0x22;
  input1[3] = 0x68;

  input2[0] = 0xFC;
  input2[1] = 0x74;
  input2[2] = 0xFB;
  input2[3] = 0x73;

  input3[0] = 0x57;
  input3[1] = 0x67;
  input3[2] = 0xCB;
  input3[3] = 0xE0;

  input4[0] = 0xC0;
  input4[1] = 0x59;
  input4[2] = 0x0E;
  input4[3] = 0x2D;

  // expected result 4C 9C 1E 66 F7 71 F0 76 2C 3F 86 8E 53 4D F2 56
  expected1[0] = 0x4C;
  expected1[1] = 0x9C;
  expected1[2] = 0x1E;
  expected1[3] = 0x66;

  expected2[0] = 0xF7;
  expected2[1] = 0x71;
  expected2[2] = 0xF0;
  expected2[3] = 0x76;

  expected3[0] = 0x2C;
  expected3[1] = 0x3F;
  expected3[2] = 0x86;
  expected3[3] = 0x8E;

  expected4[0] = 0x53;
  expected4[1] = 0x4D;
  expected4[2] = 0xF2;
  expected4[3] = 0x56;

  mixColumns((uint8_t *)input1, (uint8_t *)input2, (uint8_t *)input3, (uint8_t *)input4,
            (uint8_t *)result1, (uint8_t *)result2, (uint8_t *)result3, (uint8_t *)result4);
  munit_assert_memory_equal(4, result1, expected1);
  munit_assert_memory_equal(4, result2, expected2);
  munit_assert_memory_equal(4, result3, expected3);
  munit_assert_memory_equal(4, result4, expected4);

  // if all tests passed, return ok
  return MUNIT_OK;
}
static MunitTest aes_helper_tests[] = {
    {
        "SubBytes Tests",       /* name */
        subBytesTests,          /* test */
        NULL,                   /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "ShiftRows Tests",      /* name */
        shiftRowsTests,         /* test */
        NULL,                   /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "MixColumn Tests",      /* name */
        mixColumnsTests,        /* test */
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
    aes_helper_tests,
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
int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
  printf("AES Helper Functions Tests\n");
  // Runnin unit tests for aes helper library
  return munit_suite_main(&test_suite, (void *)"aes_helper tests", argc, argv);
}
