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
 *  @brief Radix sort the elements of a sequence of integral types.
 *  @ingroup sorting_algorithms
 *  @param   first   An iterator.
 *  @param   last    Another iterator.
 *  @tparam  _Radix  (optional) The bit width for partitioning elements.
 *  @return  Nothing.
 *
 *  @note The larger `_Radix` is, the more stack memory the algorithm takes; in
 *  all cases it should be either 8 (aka 2KB of stack) or 16 (aka 512 KB of
 *  stack).
 *
 *  The relative ordering of equivalent elements is preserved.
 */
template <std::size_t _Radix = 8, typename Iterator>
inline void radix_sort(Iterator first, Iterator last) {
    typedef std::iterator_traits<Iterator>              iter_traits;
    typedef typename iter_traits::value_type            value_type;
    typedef typename iter_traits::iterator_category     iter_category;

    static_assert(std::is_integral<value_type>::value,
                  "elements must be of an integral type");
    static_assert(_Radix <= sizeof(value_type) * 8U,
                  "radix must not exceed type width");
    // This is because the internal __radix_sort always does an even number of
    // passes.
    static_assert((sizeof(value_type) * 8U / _Radix +
                   static_cast<bool>(sizeof(value_type) * 8U % _Radix)) %
                          2 ==
                      0,
                  "ceiling of <type width> / _Radix must be even");
    static_assert(
        std::is_base_of<std::random_access_iterator_tag, iter_category>::value,
        "first and last require random access iterators");

    __radix_sort<_Radix>(first, last);
}

}  // namespace cpdsa

#endif /* CPDSA_RADIX_SORT_HPP */