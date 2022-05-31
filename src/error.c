#include <stdio.h>
#include <stdlib.h>

#include <nla/nla_error.h>
#include <nla/nla_exit.h>
#include <nla/nla_io.h>

#include "memory.h"

#define FILENAME "error.c"

struct _NLAError {
  NLAErrorType type;
  NLAString    error_name;
  NLAString    message;
};

NLAString
nla_err_type_name(NLAErrorType type) {
  char *error_name;
  switch (type) {
  case NULL_ARGUMENT_ERROR:
    error_name = "NullArgumentError";
    break;
  case INVALID_ARGUMENT_ERROR:
    error_name = "InvalidArgumentError";
    break;
  case MEMORY_ERROR:
    error_name = "MemoryError";
    break;
  case VALUE_ERROR:
    error_name = "ValueError";
    break;
  case EXIT_CALLED:
    error_name = "ExitError";
    break;
  case GENERAL_ERROR:
    error_name = "GeneralError";
    break;
  default:
    error_name = "UnnamedError";
  }

  return nla_string_new(error_name);
}

NLAError
nla_err_new(NLAErrorType type, const char *message) {
  NLAError err;
  NEW(err);
  err->type       = type;
  err->error_name = nla_err_type_name(type);

  if (message == NULL)
    err->message = nla_string_new("");
  else
    err->message = nla_string_new(message);

  return err;
}

void
nla_err_free(NLAError err) {
  if (err == NULL)
    return;

  nla_string_free(err->error_name);
  nla_string_free(err->message);

  FREE(err);
}

bool
nla_err_is_type(NLAError err, NLAErrorType type) {
  if (err == NULL)
    return false;
  return ((err->type) == type);
}

NLAErrorType
nla_err_type(NLAError err) {
  if (err == NULL)
    return -1;
  return err->type;
}

NLAString
nla_err_message(NLAError err) {
  if (err == NULL) {
    return NULL;
  }
  if (err->message == NULL)
    return NULL;

  return nla_string_copy(err->message);
}

NLAString
nla_err_name(NLAError err) {
  if (err == NULL) {
    return NULL;
  }

  return nla_string_copy(err->error_name);
}

NLAString
nla_err_str(NLAError err) {
  if (err == NULL)
    return NULL;

  char *err_name;
  if (nla_string_get(err->error_name, &err_name) < 0)
    return NULL;

  NLAString err_str;

  // no message, return only the error name
  if (err->message == NULL) {
    err_str = nla_string_new(err_name);
    if (err_str == NULL)
      goto fail;
  }
  // otherwise, return the full string
  else {
    long name_len;
    if (nla_string_len(err->error_name, &name_len) < 0)
      goto fail;

    long message_len;
    if (nla_string_len(err->message, &message_len) < 0)
      goto fail;

    char *message;
    if (nla_string_get(err->message, &message) < 0)
      goto fail;

    char err_str_buffer[500];
    if (nla_sprintf(err_str_buffer, "%s: %s", err_name, message) < 0)
      goto fail;

    err_str = nla_string_new(err_str_buffer);
    if (err_str == NULL)
      goto fail;
  }

  return err_str;

fail:
  return NULL;
}

typedef struct _NLAErrorStackNode NLAErrorStackNode;

struct _NLAErrorStackNode {
  int                line;
  NLAString          file;
  NLAString          string;
  NLAErrorStackNode *next;
};

struct _NLAErrorStack {
  NLAError           error;
  NLAErrorStackNode *node;
};

static struct _NLAErrorStack stack = {NULL, NULL};

static NLAErrorStackNode *
nla_err_stack_node_new(const char *file, int line) {
  if (file == NULL)
    return NULL;

  NLAErrorStackNode *node;
  NEW(node);

  char node_string_buffer[500];

  node->line = line;
  node->file = nla_string_new(file);

  nla_sprintf(node_string_buffer, "File \"%s\", line %i", file, line);
  node->string = nla_string_new(node_string_buffer);

  node->next = NULL;

  return node;
}

static int
nla_err_stack_node_free(NLAErrorStackNode *node) {
  if (node == NULL)
    return -1;

  nla_string_free(node->file);
  nla_string_free(node->string);
  FREE(node);
  return 0;
}

int
nla_err_raise(NLAErrorType type,
              const char  *message,
              const char  *file,
              int          line) {
  if (stack.error != NULL) {
    fprintf(stderr, "Fatal error: Error raised while error in stack\n");
    nla_exit(EXIT_FAILURE);
#ifdef TESTING
    return EXIT_CALLED;
#endif
  }

  stack.error = nla_err_new(type, message);
  stack.node  = nla_err_stack_node_new(file, line);

  return 0;
}

bool
nla_err_stack_is_err(void) {
  return stack.error != NULL;
}

void
nla_err_stack_clear(void) {

  if (stack.error == NULL)
    return;

  nla_err_free(stack.error);
  stack.error = NULL;

  NLAErrorStackNode *node      = stack.node;
  NLAErrorStackNode *next_node = node->next;
  nla_err_stack_node_free(node);
  while (next_node != NULL) {
    node      = next_node;
    next_node = node->next;
    nla_err_stack_node_free(node);
  }
  stack.node = NULL;
}

NLAError
nla_err_stack_get_err(void) {
  return stack.error;
}

int
nla_err_stack_push(const char *file, int line) {
  if (stack.error == NULL || stack.node == NULL)
    return -1;

  NLAErrorStackNode *new_node = nla_err_stack_node_new(file, line);

  new_node->next = stack.node;
  stack.node     = new_node;

  return 0;
}

bool
nla_err_stack_is_type(NLAErrorType type) {
  return nla_err_is_type(stack.error, type);
}

void
nla_err_stack_print(const char *file, int line) {
  if (stack.error == NULL)
    return;

  fprintf(stderr, "Error stack print called from %s on line %i\n", file, line);
  fprintf(stderr, "Stack trace (most recent call last):\n");

  char *string;

  NLAErrorStackNode *node = stack.node;
  while (node != NULL) {
    nla_string_get(node->string, &string);
    fprintf(stderr, "\t%s\n", string);
    node = node->next;
  }

  NLAString err_string = nla_err_str(stack.error);
  nla_string_get(err_string, &string);
  fprintf(stderr, "%s\n", string);
  nla_string_free(err_string);
}

void
nla_err_stack_check(const char *file, int line) {
  if (nla_err_stack_is_err()) {
    fprintf(stderr, "Unchecked error\n");
    fprintf(stderr, "Error stack checked on %s, line %i\n", file, line);
    nla_err_stack_print(FILENAME, __LINE__);
    nla_exit(EXIT_FAILURE);
  }
}
