//
// Copyright (c) 2019 by Victor Barbu. All Rights Reserved.
//

#pragma once

/* We define these the same for all test suites. */
#define	ASSERT_FAILURE	1	/* Failing assert status. */
#define	ASSERT_SUCCESS	0	/* Successful assert status. */

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


