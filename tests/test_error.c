#include <nla/nla_error.h>
#include <nla/nla_exit.h>

#include "nla_test.h"

#define FILENAME "tests/test_error.c"

void
test_new(void) {
  NLAError err = nla_err_new(INVALID_ARGUMENT_ERROR, "Argument is invalid");
  assert_nonnull(err);
  nla_err_free(err);
}

void
test_free(void) {
  NLAError err = nla_err_new(INVALID_ARGUMENT_ERROR, "Argument is invalid");
  assert_nonnull(err);
  nla_err_free(err);
  nla_err_free(NULL);
}

// void
// test_raise(void) {
//   assert_false(nla_err_stack_is_err());

//   NLAErrorType type = INVALID_ARGUMENT_ERROR;
//   assert_zero(nla_err_raise(type, "message", FILENAME, __LINE__));
//   assert_true(nla_err_stack_is_err());

//   NLAError err = nla_err_stack_get_err();
//   assert_nonnull(err);
//   assert_true(nla_err_is_type(err, type));

//   nla_err_stack_clear();
//   assert_false(nla_err_stack_is_err());

//   // the error should be null after the stack is cleared
//   assert_null(nla_err_stack_get_err());
//   assert_negative(nla_err_stack_push(FILENAME, __LINE__));
// }

// void
// test_stack_check(void) {
//   nla_err_stack_check(FILENAME, __LINE__);
// }

// void
// test_raise_fail(void) {

//   assert_false(nla_err_stack_is_err());

//   NLAErrorType type = INVALID_ARGUMENT_ERROR;
//   assert_zero(nla_err_raise(type, "message", FILENAME, __LINE__));
//   assert_true(nla_err_stack_is_err());

//   EXPECT_EXIT_CALL(nla_err_raise(type, "message", FILENAME, __LINE__))

//   nla_err_stack_clear();
// }

// void
// test_stack_check_fail(void) {
//   nla_err_raise(INVALID_ARGUMENT_ERROR, "", FILENAME, __LINE__);
//   nla_exit_expected_set();
//   nla_err_stack_check(FILENAME, __LINE__);
//   assert_true(nla_exit_called());
//   nla_exit_called_clear();
//   nla_err_stack_clear();
// }

int
main(void) {
  RUN_TEST_FUNC(test_new)
  // RUN_TEST_FUNC(test_free)
  // RUN_TEST_FUNC(test_raise)
  // RUN_TEST_FUNC(test_raise_fail)
  // RUN_TEST_FUNC(test_stack_check)
  // RUN_TEST_FUNC(test_stack_check_fail)

  EXIT_TEST
}
