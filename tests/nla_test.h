#include <stdio.h>
#include <stdlib.h>

#include <nla/nla_error.h>
#include <nla/nla_exit.h>

#include "nla_assert.h"

#define EXIT_TEST                                                              \
  nla_err_stack_check(FILENAME, __LINE__);                                     \
  assert_false(nla_exit_called());                                             \
  printf("Test %s ran successfully\n", FILENAME);                              \
  return EXIT_SUCCESS;

#define STR(x) #x
#define RUN_TEST_FUNC(func)                                                    \
  printf("Running test function: %s\n", STR(func));                            \
  func();

#define EXPECT_EXIT_CALL(func_call)                                            \
  nla_exit_expected_set();                                                     \
  func_call;                                                                   \
  assert_true(nla_exit_called());                                              \
  nla_exit_expected_clear();                                                   \
  nla_exit_called_clear();
