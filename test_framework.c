#include <stdio.h>
#include <unistd.h>

#define MAX_ASSERTIONS_PER_TEST 128
#define MAX_TEST_CASES 128

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

typedef void (*test_case_fn)(struct assertions_container *);

static size_t tests_count = 0;
static test_case_fn test_cases[MAX_TEST_CASES];

#define ASSERT_EQ(lhs, rhs) \
  do { \
    struct assertion __assertion = {"==", #lhs, #rhs, ((lhs) == (rhs))}; \
    cont->assertions[cont->size++] = __assertion; \
  } while (0)

void __declare_test(const char *suite, const char *name, test_case_fn fnptr)
{
  test_cases[tests_count++] = fnptr;
}

#define __TEST_FUNC_NAME(suite, test_name) __test_##suite##_##test_name

#define __TEST_FUNC_DECL(suite, test_name) \
  void __TEST_FUNC_NAME(suite, test_name)(struct assertions_container *cont)

#define TEST(suite, test_name) __TEST_FUNC_DECL(suite, test_name)

#define DECLARE_TEST(suite, test_name)                                      \
  do {                                                                      \
    __declare_test(#suite, #test_name, __TEST_FUNC_NAME(suite, test_name)); \
  } while (0)

TEST(MySuite, Something)
{
  int a = 10;
  int b = 17;

  ASSERT_EQ(a, b);
}

int main(int argc, char **argv)
{
  DECLARE_TEST(MySuite, Something);

  size_t test_idx = 0;
  for (; test_idx != tests_count; test_idx++)
  {
    struct assertions_container cont = {0};
    test_cases[test_idx](&cont);

    size_t assertion_idx = 0;
    for (; assertion_idx != cont.size; assertion_idx++)
    {
      const struct assertion *assertion = &cont.assertions[assertion_idx];
      if (!assertion->ok)
      {
        fprintf(stderr, "Test failed.\nCondition %s %s %s not met.\n",
          assertion->first_operand,
          assertion->op,
          assertion->second_operand);

        return 1;
      }
    }
  }

  return 0;
}
