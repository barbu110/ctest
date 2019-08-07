# ctest

A small testingutility for C programs.

When including in a project, please add include paths to `include`. 
The only file you will need to include in your test file is

    ctest/ctest.h
    
This will give you the following useful macros:

 - `TEST(test_suite_name, test_name)` which allows you to declare
   and define a test function. The test function MUST NOT return
   anything. It only needs to contain assertions.
 - `REGISTER_TEST(test_suite_name, test_name)` which must be called
   from the `main` function of your executable so that your newly
   added tests can be found by the test framework.
 - `ASSERT_*()` which help you write assertions for various
   conditions your application may require.
   
Also the `run_all_tests(void)` function is provided. It returns the
status of the tests being run. At the first assertion that fails, 
this function returns `1`. On success, `0` is returned.
   
# Example Usage

The project provides a very small example in `example.c` which can
be built by simply running `make`.

```c
#include "ctest/ctest.h"

int factorial(int n)
{ /* ... */ }

int series_sum(int start, int end, int step)
{ /* ... */ }

TEST(Math, Factorial)
{
  ASSERT_EQ(factorial(0), 1);
  ASSERT_EQ(factorial(1), 1);
  ASSERT_EQ(factorial(4), 24);
}

TEST(Math, SeriesSum)
{
  ASSERT_EQ(series_sum(1, 10, 1), 55);
  ASSERT_EQ(series_sum(0, 0, 1), 0);
  ASSERT_EQ(series_sum(0, 1, 10), 0);
}

int main()
{
  REGISTER_TEST(Math, Factorial);
  REGISTER_TEST(Math, SeriesSum);
  
  return run_all_tests();
} 
  
```
