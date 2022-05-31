#include <stdlib.h>

#include <nla/nla_exit.h>

#include "nla_test.h"

#define FILENAME "tests/test_exit.c"

int
main(void) {

  nla_exit_expected_set();
  nla_exit(EXIT_FAILURE);
  assert_true(nla_exit_called());
  assert_equal(nla_exit_status(), EXIT_FAILURE);
  nla_exit_expected_clear();
  nla_exit_called_clear();

  EXIT_TEST
}
