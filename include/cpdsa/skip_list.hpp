/**
 * CPDSA: Skip list implementation -*- C++ -*-
 *
 * @file include/cpdsa/src/skip_list.hpp
 */

#ifndef CPDSA_SKIP_LIST
#define CPDSA_SKIP_LIST

namespace cpdsa {

/**
 * @brief Types eligible to be elements of @c skip_list.
 */
#if __cplusplus >= 202002L
template <typename _Tp>
concept Skip_list_element_type = requires(_Tp a, _Tp b) { a < b; };
#else
// shit goes here
#endif

/**
 * @brief A container maintaining elements in increasing order
 *
 */
template<Skip_list_element_type _Tp>
class skip_list {

};

}  // namespace cpdsa

#endif /* CPDSA_SKIP_LIST */
