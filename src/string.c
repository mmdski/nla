#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <nla/nla_string.h>

#include "memory.h"

struct _NLAString {
  long  len;
  char *string;
};

static NLAString
nla_string_new_empty(long len) {
  NLAString s;
  NEW(s);

  char *string = nla_calloc(len, sizeof(char));

  if (string == NULL) {
    return NULL;
  }

  s->len    = len;
  s->string = string;

  return s;
}

static int
nla_string_fill(NLAString s, const char *string) {
  if (s == NULL || string == NULL) {
    return -1;
  }

  long len = s->len;

  for (long i = 0; i < len; i++) {
    s->string[i] = string[i];
  }

  return 0;
}

NLAString
nla_string_new(const char *string) {
  if (string == NULL) {
    return NULL;
  }

  long       len     = 1;
  const long MAX_LEN = 500;

  while (true) {
    if (string[len - 1] == '\0') {
      break;
    } else if (len >= MAX_LEN) {
      break;
    } else
      len++;
  }

  NLAString s = nla_string_new_empty(len);
  if (s == NULL) {
    return NULL;
  }

  if (nla_string_fill(s, string) < 0) {
    nla_string_free(s);
    return NULL;
  }

  return s;
}

void
nla_string_free(NLAString s) {
  if (s == NULL) {
    return;
  }
  nla_free(s->string);
  FREE(s);
  return;
}

NLAString
nla_string_copy(NLAString s) {
  if (s == NULL)
    return NULL;

  NLAString s_copy = nla_string_new(s->string);

  return s_copy;
}

bool
nla_string_eq(NLAString a, NLAString b) {
  if (a == NULL || b == NULL)
    return false;

  if (a == b)
    return true;

  return strcmp(a->string, b->string) == 0;
}

int
nla_string_get(NLAString s, char **string) {
  if (s == NULL || string == NULL) {
    return -1;
  }
  *string = s->string;
  return 0;
}

int
nla_string_len(NLAString s, long *len) {
  if (s == NULL || len == NULL) {
    return -1;
  }

  *len = s->len;

  return 0;
}
