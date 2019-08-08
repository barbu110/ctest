//
// Copyright (c) 2019 by Victor Barbu. All Rights Reserved.
//

#pragma once

/* We define these the same for all test suites. */

#define EQ               ==
#define LT                <
#define GT                >

#define ASSERT_FAILURE    1 /* Failing assert status. */
#define ASSERT_SUCCESS    0 /* Successful assert status. */

#define IOPS $(SUB,-) $(ADD,+) $(MUL,*) $(DIV,/) $(MOD,%) $(AND,&) $(OR,|) \
  $(XOR,^) $(SR,>>) $(SL,<<) $(MEQ,==) $(MLT,<) $(MGT,>) $(MLE,<=) $(MGE,>=)

enum iops_enum
{
#define $(x,op)   IOPSENUM_##x,
  IOPS
  IOPSENUM_COUNT
#undef $
};

int opi(int a, enum iops_enum b, int c);

#define ASSERT_NEQ(lhs, rhs)                                             \
  do {                                                                   \
    struct assertion __assertion = {"!=", #lhs, #rhs, ((lhs) != (rhs))}; \
    cont->assertions[cont->size++] = __assertion;                        \
  } while (0)

#define ASSERT_EQ(lhs, rhs)                                              \
  do {                                                                   \
    struct assertion __assertion = {"==", #lhs, #rhs, ((lhs) == (rhs))}; \
    cont->assertions[cont->size++] = __assertion;                        \
  } while (0)

#define ASSERT_LT(lhs, rhs)                                            \
  do {                                                                 \
    struct assertion __assertion = {"<", #lhs, #rhs, ((lhs) < (rhs))}; \
    cont->assertions[cont->size++] = __assertion;                      \
  } while (0)

#define ASSERT_GT(lhs, rhs)                                            \
  do {                                                                 \
    struct assertion __assertion = {">", #lhs, #rhs, ((lhs) > (rhs))}; \
    cont->assertions[cont->size++] = __assertion;                      \
  } while (0)

#define ASSERT_LTE(lhs, rhs)                                             \
  do {                                                                   \
    struct assertion __assertion = {"<=", #lhs, #rhs, ((lhs) <= (rhs))}; \
    cont->assertions[cont->size++] = __assertion;                        \
  } while (0)

#define ASSERT_GTE(lhs, rhs)                                             \
  do {                                                                   \
    struct assertion __assertion = {">=", #lhs, #rhs, ((lhs) >= (rhs))}; \
    cont->assertions[cont->size++] = __assertion;                        \
  } while (0)

#define ASSERT_STRCMP(lhs, rhs, EXPECTED_RELATION)                        \
  do {                                                                    \
    char result = strcmp(lhs, rhs);                                       \
    char var = opi(result, EXPECTED_RELATION, 0);                         \
    struct  assertion __assertion = {"", #lhs, #rhs, var};                \
    cont->assertions[cont->size++] = __assertion;                         \
  } while (0)
