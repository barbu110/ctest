/*
 * Copyright (c) 2019 by Victor Barbu and Alexandru - George Rusu. All Rights Reserved.
 */

#include "ctest/ctest.h"
#include "ctest/assertions.h"

#include <stdio.h>
#include <string.h> ///< strcmp()

TEST(Basic, MathRelation)
{
  int a = 10;
  int b = 20;

  ASSERT_LT(a, b);
}

TEST(Basic, Equality)
{
  int a = 10;
  int b = 10;

  ASSERT_EQ(a, b);
}

TEST(Modern, LessThanOrEqual)
{
  int a = 10;
  int b = 20;

  ASSERT_LTE(a, b);
}

TEST(Modern, GreaterThanOrEqual)
{
  int a = 18;
  int b = 17;

  ASSERT_GTE(a, b);
}

TEST(Modern, TestStr)
{
  char *a = "my_string1";
  char *b = "my_string1";

 ASSERT_STRCMP(a, b, IOPSENUM_MEQ);
}

void load_suites()
{
  REGISTER_TEST(Basic, MathRelation);
  REGISTER_TEST(Basic, Equality);

  REGISTER_TEST(Modern, LessThanOrEqual);
  REGISTER_TEST(Modern, GreaterThanOrEqual);
  REGISTER_TEST(Modern, TestStr);
}

int main(int argc, char **argv)
{
  load_suites();
  _ctest_main(argc, argv);
}
