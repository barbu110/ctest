/*
 * Copyright (c) 2019 by Victor Barbu and Alexandru - George Rusu. All Rights Reserved.
 */

#include "ctest/ctest.h"
#include "ctest/assertions.h"

#include <stdio.h>
#include <string.h> ///< strcmp()
#include <stdlib.h> ///< exit()

#define NR_SUITES 3

char *my_suites[NR_SUITES] = {"Basic", "Undefined", "Modern"};

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
  char *b = "my_string";

 ASSERT_STRCMP(a, b, IOPSENUM_MEQ);
}

void register_basic_tests()
{
  REGISTER_TEST(Basic, MathRelation);
  REGISTER_TEST(Basic, Equality);
}

void register_modern_tests()
{
  REGISTER_TEST(Modern, LessThanOrEqual);
  REGISTER_TEST(Modern, GreaterThanOrEqual);
  REGISTER_TEST(Modern, TestStr);
}

void *register_suite_tests[NR_SUITES] = {register_basic_tests, NULL, register_modern_tests};

void load_suites()
{
  char j = 0;

  while(j != NR_SUITES)
  {
    if(register_suite_tests[j] != NULL)
    {
      printf("Suite %s registered.\n", my_suites[j]);
      ((void (*)())(register_suite_tests[j]))();
    }
    j++;
  }
}

void print_usage()
{
  fprintf(stderr, "Usage: ./example [OPTION] [ARG]\n"
      "supported suites: Basic, Modern\n"
      "--help shows this description\n"
      "--all runs all supported suites\n"
      "--suite <suite_name> runs all the tests registered within the given suite_name\n");
}

int main(int argc, char **argv)
{
  char i, j = 0;

  if(argc < 2)
  {
    fprintf(stderr, "Not enough arguments, check the usage below\n\n");
    print_usage();
    exit(EXIT_FAILURE);
  }

  for(i = 1; i < argc; i++)
  {
    if(!(strcmp(argv[i], "--all")))
    {
      load_suites();
      break;
    }
    else if(!(strcmp(argv[i], "--suite")))
    {
      while(j != NR_SUITES)
      {
        if(!(strcmp(my_suites[j], argv[i + 1])))
        {
          printf("Suite %s registered.\n", my_suites[j]);
          ((void (*)())(register_suite_tests[j]))();
          j = 0; i++;
          break;
        }
        j++;
      }
    }
    else if(!(strcmp(argv[i], "--help")))
    {
      print_usage();
      exit(EXIT_SUCCESS);
    }
    else
    {
      fprintf(stderr, "Unknown test/option '%s' specified. Use --help to see the valid options.\n\n", argv[i]);
      exit(EXIT_FAILURE);
    }

  }

  printf("\nRunning test suites.\n");
  run_all_tests();
  exit(EXIT_SUCCESS);
}
