// Direct input from buffer -*- C++ -*-

#ifndef CPDSA_BUFFER_INPUT
#define CPDSA_BUFFER_INPUT

#include "impl/buffer_scan_base.hpp"

namespace cpdsa {

/**
 * @brief Scan for integral numbers by reading batches of 65536 chars
 * from `stdin`. The first such number found is assigned to the first argument,
 * and so on.
 *
 * @note This function uses exclusively input functions from `stdio`.
 * `std::sync_with_stdio(0)` therefore will unsync this from `cin`. In any
 * cases, it is HIGHLY RECOMMENDED that this function is the only input reader
 * in the entire program. Know what you are doing. Also note that this function
 * bundles a static array of 65536 chars. Embedded devices may not like this.
 */
template <std::integral _Tp, std::integral... _Tps>
constexpr void buffer_scan(_Tp& first_arg, _Tps&... rest_args) noexcept {
    first_arg = getd<_Tp>();
    buffer_scan(rest_args...);
}

}  // namespace cpdsa

#endif /* CPDSA_BUFFER_INPUT */