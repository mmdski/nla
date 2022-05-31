/**
 * @file nla_string.h
 * @brief String interface
 */

#ifndef __NLA_STRING_H__
#define __NLA_STRING_H__

#include <stdbool.h>

/**
 * String object
 */
typedef struct _NLAString *NLAString;

/**
 * @brief Creates a new string
 *
 * @details Creates a new string from a null-terminated array of characters.
 * This function returns @c NULL if creation fails. The returned string must be
 * freed with nla_string_free() when no longer in use.
 *
 * @param string null-terminated string
 * @return new string
 */
extern NLAString nla_string_new(const char *string);

/**
 * @brief Frees a string
 *
 * @param s a string
 */
extern void nla_string_free(NLAString s);

/**
 * @brief Copies a string
 *
 * @param s string to copy
 * @return a copy of s
 */
extern NLAString nla_string_copy(NLAString s);

/**
 * @brief Returns true if two strings are equal
 *
 * @param a a string
 * @param b another string
 * @return true if two strings are equal, false otherwise
 */
extern bool nla_string_eq(NLAString a, NLAString b);

/**
 * @brief Gets the character array contained in a string
 *
 * @param s a string
 * @param string a pointer to a character array
 * @returns 0 if operation was a success, -1 otherwise
 */
extern int nla_string_get(NLAString s, char **string);

/**
 * @brief Gets the length of a string
 *
 * @details Gets the length of a string including the null character.
 *
 * @param s a string
 * @param len a pointer to a long that contains the length of s
 * @returns 0 if operation was a success, -1 otherwise
 */
extern int nla_string_len(NLAString s, long *len);

#endif
