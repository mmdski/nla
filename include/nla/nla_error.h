/**
 * @file nla_error.h
 * @brief Error definitions
 */

#ifndef __NLA_ERR_H__
#define __NLA_ERR_H__

#include <nla/nla_string.h>
#include <stdbool.h>

/**
 * Error types
 */
typedef enum {

  /** The negative of this number is the number of error types */
  NEG_NUM_ERROR_TYPES = -7,

  /** Null argument error */
  NULL_ARGUMENT_ERROR,

  /** Invalid argument error */
  INVALID_ARGUMENT_ERROR,

  /** Memory error */
  MEMORY_ERROR,

  /** Value error */
  VALUE_ERROR,

  /** nla_exit() has been called */
  EXIT_CALLED,

  /** General error */
  GENERAL_ERROR

} NLAErrorType;

/**
 * nlaib error object
 */
typedef struct _NLAError *NLAError;

/**
 * @brief Creates a new error object
 *
 * @details The error object must be freed with nla_err_free().
 *
 * @param type error type
 * @param message error message
 */
extern NLAError nla_err_new(NLAErrorType type, const char *message);

/**
 * @brief Frees an error object.
 *
 * @param err error object
 */
extern void nla_err_free(NLAError err);

/**
 * @brief Returns true if an error object is of a specified type.
 *
 * @param err an error object
 * @param type an error type
 * @returns true if @c err is of type @c type, false otherwise
 */
extern bool nla_err_is_type(NLAError err, NLAErrorType type);

/**
 * @brief Returns the message of an error
 *
 * @param err an error object
 * @returns the message of @c err
 */
extern NLAString nla_err_message(NLAError err);

/**
 * @brief Returns the name the type of an error
 *
 * @param err an error object
 * @returns the name of the error type of @c err
 */
extern NLAString nla_err_name(NLAError err);

/**
 * @brief Returns the string representation of an error
 *
 * @details The string representation of an error is
 *
 * <code>[error type name]: [error message]</code>
 *
 * @param err an error object
 * @returns the string representation of @c err
 */
extern NLAString nla_err_str(NLAError err);

/**
 * @brief Returns the type of an error
 *
 * @param err an error object
 * @returns the error type of @c err
 */
extern NLAErrorType nla_err_type(NLAError err);

/**
 * @brief Puts an error on the error stack and initializes the first line of the
 * stack
 *
 * @param type error type
 * @param message error message
 * @param file file name
 * @param line line number (use __LINE__ macro)
 * @return 0 if successful, -1 otherwise
 */
extern int nla_err_raise(NLAErrorType type,
                         const char  *message,
                         const char  *file,
                         int          line);

/**
 * @brief Returns true if an error is on the error stack, false otherwise
 *
 * @return true or false
 */
extern bool nla_err_stack_is_err(void);

/**
 * @brief Clears the error stack
 */
extern void nla_err_stack_clear(void);

/**
 * @brief Pushes a new line on the error stack
 *
 * @param file file name
 * @param line line number (use __LINE__ macro)
 * @return 0 if successful, -1 otherwise
 */
extern int nla_err_stack_push(const char *file, int line);

/**
 * @brief Returns the error currently on the error stack
 *
 * @details The returned error is a reference to the error on the stack. Do not
 * free outside of nla_err_stack_clear().
 *
 * @return error currently on the stack
 */
extern NLAError nla_err_stack_get_err(void);

/**
 * @brief Checks the error type on the error stack
 *
 * @param type error type
 * @return true if @p type is the type of error on the stack
 * @return false if @p type is not the type of error on the stack
 */
extern bool nla_err_stack_is_type(NLAErrorType type);

/**
 * @brief Print the error stack to @c stderr
 *
 * @param file file name
 * @param line line number (use __LINE__ macro)
 */
extern void nla_err_stack_print(const char *file, int line);

/**
 * @brief Checks for an error on stack.
 *
 * @details If an error on the stack exists, prints the stack and exits the
 * program.
 *
 * @param file file name
 * @param line line number (use __LINE__ macro)
 */
extern void nla_err_stack_check(const char *file, int line);

#endif
