//
// Copyright (c) 2019 by Victor Barbu. All Rights Reserved.
//

#include "ctest/ctest.h"
#include "ctest/assertions.h"

#include <stdio.h>

TEST(Basic, MathRelation)
{
  int a = 10;
  int b = 20;

  ASSERT_LT(a, b);
}

TEST(Basic, Equality)
{
  int a = 10;
  int b = 17;

  ASSERT_EQ(a, b);
}

int main(int argc, char **argv)
{
  REGISTER_TEST(Basic, MathRelation);
  REGISTER_TEST(Basic, Equality);


  run_all_tests();

  return 0;
}
