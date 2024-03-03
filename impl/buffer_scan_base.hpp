// Direct input from buffer, base implementation -*- C++ -*-

#ifndef CPDSA_BUFFER_INPUT_BASE
#define CPDSA_BUFFER_INPUT_BASE

#include <ctype.h>   // for size_t
#include <stdio.h>   // for fread
#include <concepts>  // for std::integral

namespace cpdsa {
/**
 * @brief Get the next 8 bits from stdin.
 *
 * @return Either the result or `EOF`.
 */
char getc() noexcept {
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
 * @brief Get the next integral number from stdin.
 *
 * @return Return said number or 0 if no number is found.
 *
 * @note First skips non-digit characters except `-`. If `-` is reached
 * first then number is considered negative. Stops upon reaching any non-digit
 * character. Will most likely cause overflow if too much digit has been readed.
 */
template <std::integral _Tp>
[[nodiscard]] constexpr _Tp getd() noexcept {
    char is_negative = false;
    int next_char;
    while (!isdigit(next_char = getc()) && next_char != '-')
        ;
    if (next_char == '-')
        is_negative = true, next_char = getc();
    _Tp unsigned_result = 0;
    for (; isdigit(next_char); next_char = getc())
        unsigned_result *= 10, unsigned_result += next_char - '0';
    return (is_negative ? -unsigned_result : unsigned_result);
}

/**
 * @brief A function that does nothing (by design).
 */
void buffer_scan() {}

}  // namespace cpdsa

#endif /* CPDSA_BUFFER_INPUT_BASE */
