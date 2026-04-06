/**
 * CPDSA: Skip list -*- C++ -*-
 *
 * @file include/cpdsa/src/skip_list.hpp
 */

#ifndef CPDSA_SKIP_LIST
#define CPDSA_SKIP_LIST

#include <concepts>
#include "./base/skip_list_base.hpp"

namespace cpdsa {

/**
 * @brief Types eligible to be elements of @c skip_list.
 */
#if __cplusplus >= 202002L
template <typename _Tp>
concept Skip_list_element_type = std::three_way_comparable<_Tp>;
#else
// shit goes here
#endif

/**
 * @brief A container maintaining *unique* elements in increasing order.
 */
template <Skip_list_element_type _Tp>
class skip_list {
    using iterator = _Tp*;              // stub
    using const_iterator = const _Tp*;  // another stub

    iterator insert(const _Tp& val) {}
    iterator erase(const _Tp& val) {}

    [[nodiscard]] iterator find(const _Tp& val) {}
    iterator begin();
    iterator end();

    void clear() {}
};

}  // namespace cpdsa

#endif /* CPDSA_SKIP_LIST */
