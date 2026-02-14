/**
 * CPDSA: Direct input from buffer, base implementation -*- C++ -*-
 * This is essentially a C source file.
 *
 * @file src/base/buffer_scan_base.hpp
 */

#ifndef CPDSA_BUFFER_SCAN_BASE
#define CPDSA_BUFFER_SCAN_BASE

#include <ctype.h>   // isdigit
#include <stddef.h>  // size_t
#include <stdio.h>   // fread

namespace cpdsa {

/**
 * @brief Get the next 8 bytes from stdin, or return @a EOF if stdin is
 * empty.
 *
 * @note Use @c fread() to perform efficient bulk reading.
 */
[[nodiscard]] char __getc() noexcept {
    // testing shows that 64 KB is a sweet spot
    static const size_t BUFSIZE = 1 << 16;
    static char buf[BUFSIZE];
    static size_t bufat = 0, bufend = 0;
    if (bufat == bufend) {
        bufend = fread(buf, sizeof(char), BUFSIZE, stdin);
        bufat = 0;
    }
    return bufend ? buf[bufat++] : EOF;
}

/**
 * @brief Get the next integral number from @c stdin.
 *
 * @return Return said number or @a 0 if no number is found.
 *
 * @note First skips non-digit characters except @a - and @a +. If @a - is
 * reached first then the number is considered negative. After that,
 * continuously reads characters until reaching any non-digit ones. Will most
 * likely cause overflow if too much digit has been readed.
 */
template <typename _Tp>
[[nodiscard]] _Tp getd() noexcept {
    bool is_negative = false;
    int next_char = 0;
    while (!isdigit(next_char = __getc()) && next_char != '-') {
        if (next_char == EOF) return 0;
    }
    if (next_char == '-') is_negative = true, next_char = __getc();
    _Tp unsigned_result = 0;
    for (; isdigit(next_char); next_char = __getc())
        unsigned_result = unsigned_result * 10 + next_char - '0';  // compiler will figure this one out
    return (is_negative ? -unsigned_result : unsigned_result);
}

/**
 * @brief A function that does nothing (by design).
 */
void buffer_scan() {}

}  // namespace cpdsa

#endif /* CPDSA_BUFFER_SCAN_BASE */