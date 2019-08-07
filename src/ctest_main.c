//
// Copyright (c) 2019 by Victor Barbu. All Rights Reserved.
//

#include "ctest/ctest.h"

#include <stdio.h>
#include <unistd.h>

void __register_test(const char *suite, const char *name, test_fn fn)
{
  struct test_case __test_case = {suite, name, fn};
  test_cases[tests_count++] = __test_case;
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

        return 1;
      }
    }

    printf("[PASSED] %s::%s\n", test_case->suite, test_case->test_name);
  }

  return 0;
}
