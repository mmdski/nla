#include <stdlib.h>

extern void *nla_alloc(size_t nbytes);

extern void *nla_calloc(size_t count, size_t nbytes);

extern void nla_free(void *ptr);

#define ALLOC(nbytes) nla_alloc((nbytes))
#define NEW(p) ((p) = ALLOC(sizeof *(p)))
#define FREE(ptr) ((void) (nla_free((ptr)), (ptr) = 0))
