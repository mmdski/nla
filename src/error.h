#ifndef __ERR_H__
#define __ERR_H__
#include <stdlib.h>

#define RAISE_NULL_ERR_INT                                                     \
  {                                                                            \
    nla_err_raise(NULL_ARGUMENT_ERROR, NULL, FILENAME, __LINE__);              \
    return -1;                                                                 \
  }

#define RAISE_NULL_ERR_NULL                                                    \
  {                                                                            \
    nla_err_raise(NULL_ARGUMENT_ERROR, NULL, FILENAME, __LINE__);              \
    return NULL;                                                               \
  }

#define RAISE_ARG_ERR_INT                                                      \
  {                                                                            \
    nla_err_raise(INVALID_ARGUMENT_ERROR, NULL, FILENAME, __LINE__);           \
    return -1;                                                                 \
  }

#define RAISE_ARG_ERR_NULL                                                     \
  {                                                                            \
    nla_err_raise(INVALID_ARGUMENT_ERROR, NULL, FILENAME, __LINE__);           \
    return NULL;                                                               \
  }

#endif
