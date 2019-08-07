#include <stdio.h>
#include <unistd.h>

enum bool
{
  TRUE = 1,
  FALSE = 0,
};

typedef enum bool bool_t;

struct assertion
{
  const char *operation;
  const char *first_operand;
  const char *second_operand;
  bool_t ok;
};

static const size_t max_assertions_per_test = 128;

struct assertions_container
{
  size_t size;
  struct assertion *assertions;
};

typedef void (*test_case_fn)(struct assertions_container *);

static const int max_test_cases_count = 128;
static size_t tests_count = 0;
static test_case_fn test_cases[max_test_cases_count];

#define ASSERT_EQ(op1, op2, cont)   \
  do { cont->data[cont->size++] = { \
    "==",                           \
    #op1,                           \
    #op2,                           \
    (op1) == (op2)                  \
  }; } while(0)

#define __TEST_FUNC_NAME(suite, test_name) \
  __test_##suite##_##test_name

#define __TEST_FUNC_DECL(suite, test_name) \
  void __TEST_FUNC_NAME(struct assertions_container *)

#define TEST(suite, test_name)                                  \
  __TEST_FUNC_DECL(suite, test_name);                           \
  test_cases[tests_count] = __TEST_FUNC_NAME(suite, test_name); \
  __TEST_FUNC_DECL(suite, test_name)

TEST(MySuite, Something)
{
  int a = 10;
  int b = 17;

  ASSERT_EQ(a, b, c);
}

int main(int argc, char **argv)
{
  size_t test_idx = 0;
  for (; test_idx != tests_count; test_idx++)
  {
    struct assertions_container cont = {0};
    test_cases[test_idx](&cont);

    size_t assertion_idx = 0;
    for (; assertion_idx != cont.size; assertion_idx++)
    {
      const struct assertion *assertion = &cont.data[assertion_idx];
      if (!assertion->ok)
      {
        fprintf(stderr, "Test failed.\nParams %s and %s.\n",
          assertion->first_operand,
          assertion->second_operand);

        return 1;
      }
    }
  }
}
