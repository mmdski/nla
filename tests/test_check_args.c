#include <stdio.h>
#include <stdlib.h>

#include <nla/nla_error.h>

int
main(void) {
#ifdef CHECK_ARGS
  return EXIT_SUCCESS;
#else
  return EXIT_FAILURE;
#endif
}
