#ifndef __nla_EXIT__
#define __nla_EXIT__

#ifdef TESTING
#include <stdbool.h>

/**
 * @brief Perform normal program termination
 *
 * @details This function is defined for testing purposes when -DTESTING is set.
 * If the exit expected flag is set after using nla_exit_expected_set(), the
 * program doesn't terminate. The call status of this function can be checked
 * with nla_exit_called(), and the call flag can ge cleared with
 * nla_exit_called_clear(). The program will terminate if the expected flag is
 * not set or if the called flag has not been cleared.
 *
 * @param status exit status
 */
extern void nla_exit(int status);

/**
 * @brief Checks the nla_exit() call status flag
 *
 * @return true
 * @return false
 */
extern bool nla_exit_called(void);

/**
 * @brief Clears the nla_exit() call status flag
 *
 */
extern void nla_exit_called_clear(void);

/**
 * @brief Sets the nla_exit() call expected flag
 *
 */
extern void nla_exit_expected_set(void);

/**
 * @brief Clears the nla_exit() call expected flag
 *
 */
extern void nla_exit_expected_clear(void);

/**
 * @brief Returns the status from the nla_exit() call
 *
 * @return int the exit status
 */
extern int nla_exit_status(void);

#else

#define nla_exit(status) exit(status)

#endif
#endif
