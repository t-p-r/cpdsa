/**
 * CPDSA: Radix sort with 2^16 radix -*- C++ -*-
 *
 * @file src/radix_sort.hpp
 */

#ifndef CPDSA_RADIX_SORT_HPP
#define CPDSA_RADIX_SORT_HPP

#include "base/radix_sort_base.hpp"

namespace cpdsa {

/**
 *  @brief Sort the elements of a sequence of integral types.
 *  @ingroup sorting_algorithms
 *  @param   first   An iterator.
 *  @param   last    Another iterator.
 *  @return  Nothing.
 *
 *  @note Sorts the elements in the range `[first, last)` in ascending order,
 *  such that for each iterator `i` in the range `[first, last - 1)`,
 *  `*(i+1) < *i` is false.
 *
 *  The relative ordering of equivalent elements is preserved.
 */
template <typename Iterator>
inline void radix_sort(Iterator first, Iterator last) {
    typedef std::iterator_traits<Iterator>              iter_traits;
    typedef typename iter_traits::value_type            value_type;
    typedef typename iter_traits::iterator_category     iter_category;

    static_assert(
        std::is_base_of<std::random_access_iterator_tag, iter_category>::value,
        "first and last require random access iterators");

    static_assert(std::is_integral<value_type>::value,
                  "elements must be of an integral type");

#if __cplusplus >= 201703L
    if constexpr (sizeof(value_type) <= 4) {  // pedantic moment
#else
    if (sizeof(value_type) <= 4) {
#endif
        __radix_sort_32(first, last);
    } else {
        __radix_sort_64(first, last);
    }
}

}  // namespace cpdsa

#endif /* CPDSA_RADIX_SORT_HPP */