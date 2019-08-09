/*
 * Copyright (c) 2019 by Victor Barbu and Alexandru - George Rusu. All Rights Reserved.
 */

#pragma once

#include <unistd.h>

#include "ctest/assertions.h"

#define _STRINGIFY(s) #s
#define STRINGIFY(s) _STRINGIFY(s)

#ifndef SUITE
#define SUITE __ALL__
#endif

#define MAX_ASSERTIONS_PER_TEST 128
#define MAX_TEST_CASES 128

struct assertions_container;
typedef void (*test_fn)(struct assertions_container *);

struct test_case
{
  const char *suite;
  const char *test_name;
  test_fn fn;
};

static size_t tests_count = 0;
static struct test_case test_cases[MAX_TEST_CASES];

struct assertion
{
  const char *op;
  const char *first_operand;
  const char *second_operand;
  int ok;
};

struct assertions_container
{
  size_t size;
  struct assertion assertions[MAX_ASSERTIONS_PER_TEST];
};

void __register_test(const char *suite, const char *name, test_fn fn);

#define __TEST_FUNC_NAME(suite, test_name) __test_##suite##_##test_name

#define __TEST_FUNC_DECL(suite, test_name)                                   \
  void __TEST_FUNC_NAME(suite, test_name)(struct assertions_container *cont)

#define TEST(suite, test_name) __TEST_FUNC_DECL(suite, test_name)

#define REGISTER_TEST(suite, test_name)                                      \
  do {                                                                       \
    __register_test(#suite, #test_name, __TEST_FUNC_NAME(suite, test_name)); \
  } while (0)

int run_all_tests();

int _ctest_main(int argc, char **argv);
