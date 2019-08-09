/*
 * Copyright (c) 2019 by Victor Barbu and Alexandru - George Rusu. All Rights Reserved.
 */

#include "ctest/ctest.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> ///< exit()
#include <string.h> ///< strcmp()

void __register_test(const char *suite, const char *name, test_fn fn)
{
  if((!(strcmp(suite, STRINGIFY(SUITE)))) || (!(strcmp(STRINGIFY(SUITE), "__ALL__"))))
  {
    struct test_case __test_case = {suite, name, fn};
    test_cases[tests_count++] = __test_case;
  }
  return;
}

int run_all_tests()
{
  size_t test_idx = 0;
  for (; test_idx != tests_count; test_idx++)
  {
    const struct test_case *test_case = &test_cases[test_idx];
    struct assertions_container cont = {0};
    (test_case->fn)(&cont);

    size_t assertion_idx = 0;
    for (; assertion_idx != cont.size; assertion_idx++)
    {
      const struct assertion *assertion = &cont.assertions[assertion_idx];
      if (!assertion->ok)
      {
        fprintf(
          stderr,
          "[FAILED] %s::%s\n"
          "    Assertion: \"%s %s %s\" not met.\n",
          test_case->suite, test_case->test_name,
          assertion->first_operand, assertion->op, assertion->second_operand
        );

        return ASSERT_FAILURE;
      }
    }

    printf("[PASSED] %s::%s\n", test_case->suite, test_case->test_name);
  }

  printf("\nAll tests have been passed.\n");
  return ASSERT_SUCCESS;
}

int _ctest_main(int argc, char **argv)
{
  printf("\nRunning test suites.\n\n");
  run_all_tests();
  exit(EXIT_SUCCESS);
}
