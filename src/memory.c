#include <stdlib.h>

void *
nla_alloc(size_t nbytes) {
  return malloc(nbytes);
}

void *
nla_calloc(size_t count, size_t nbytes) {
  return calloc(count, nbytes);
}

void
nla_free(void *ptr) {
  free(ptr);
}
