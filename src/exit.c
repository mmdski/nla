#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool expected = false;
bool called   = false;
int  status;

void
nla_exit_expected_set(void) {
  expected = true;
}

void
nla_exit_expected_clear(void) {
  expected = false;
}

void
nla_exit(int exit_status) {
  if (expected) {
    puts("Caught expected call to nla_exit()");
    called = true;
    status = exit_status;
  } else if (called) {
    fputs("Fatal Error: nla_exit() call flag already set", stderr);
    exit(EXIT_FAILURE);
  } else {
    fputs("Fatal Error: Unexpected call to nla_exit()", stderr);
    exit(exit_status);
  }
}

bool
nla_exit_called(void) {
  return called;
}

void
nla_exit_called_clear(void) {
  called = false;
}

int
nla_exit_status(void) {
  return status;
}
