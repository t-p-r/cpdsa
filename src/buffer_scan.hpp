/** 
 * CPDSA: Direct input from buffer -*- C++ -*-
 * Other than a few C++ type checks this is essentially a C source file.
 * That is why, for example, you will see size_t instead of std::size_t.
 *
 * @file src/buffer_scan.hpp
 */

#ifndef CPDSA_BUFFER_SCAN
#define CPDSA_BUFFER_SCAN

#include "base/buffer_scan_base.hpp"

namespace cpdsa {

/**
 * @brief Scan for integral numbers by reading batches of @a BUFSIZE (defaulted
 * to 65536) chars from stdin. The first such number found is assigned to the
 * first argument, and so on.
 *
 * @note This function uses exclusively input functions from @c stdio.
 * @c std::sync_with_stdio(0) therefore will unsync this from @c cin. In any
 * cases, it is @e highly recommended that this function is the only input
 * reader in the entire program. @e Know what you are doing. Also note that this
 * function bundles a static array of @a 65536 chars. Embedded devices may not
 * like this.
 */
#if __cplusplus >= 202002L
template <std::integral _Tp, std::integral... _Tps>
#else
template <typename _Tp, typename... _Tps>
#endif
void buffer_scan(_Tp &first_arg, _Tps &...rest_args) noexcept {
#if __cplusplus < 202002L
    static_assert(std::is_integral<_Tp>::value, "arguments must be integral");
#endif
    first_arg = getd<_Tp>();
    buffer_scan(rest_args...);
}

}  // namespace cpdsa

#endif /* CPDSA_BUFFER_SCAN */