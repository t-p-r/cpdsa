// Direct input from buffer -*- C++ -*-

#include "impl/buffer_scan_base.hpp"

#ifndef CPDSA_BUFFER_INPUT
#define CPDSA_BUFFER_INPUT

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
constexpr void buffer_scan(_Tp& n, _Tps&... args) noexcept {
    n = getd<_Tp>();
    buffer_scan(args...);
}

}  // namespace cpdsa

#endif /* CPDSA_BUFFER_INPUT */