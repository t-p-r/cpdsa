/**
 * CPDSA: radix sort internal -*- C++ -*-
 *
 * @file src/base/radix_sort_base.hpp
 */

#ifndef RADIX_SORT_BASE_HPP
#define RADIX_SORT_BASE_HPP

#include <algorithm>
#include <array>
#include <type_traits>
#include <vector>

namespace cpdsa {

/**
 * @brief Bucket sort the sequence `[source_first, source_last)`, put result
 * in
 * `[dest_first, dest_first + source_last - source_first)`
 * @param offset this means that element X will be put into bucket number Y,
 * where Y is the number represented by 8/16 bits immediately following the
 * offset_th bit of X
 * @note The relative ordering of equivalent elements is preserved.
 */
template <std::size_t _Bucket_size,
          typename IteratorSource,
          typename IteratorDest,
          typename value_type =
              typename std::iterator_traits<IteratorSource>::value_type>
inline void __do_bucket_sort(IteratorSource source_first,
                             IteratorSource source_last,
                             IteratorDest dest_first,
                             std::size_t offset) {
    const std::size_t N_elem = std::distance(source_first, source_last);
    auto radix_func = [offset](value_type s) {
        return ((s >> offset) & (_Bucket_size - 1));
    };
    // note: add 256-512KB to stack for 16-bit radix
    std::array<std::size_t, _Bucket_size> bucket;
    // note: fill() can decay to memset
    bucket.fill(0);
    // TODO: replace with SIMD
    for (auto it = source_first; it != source_last; ++it)
        bucket[radix_func(*it)]++;
    std::partial_sum(bucket.begin(), bucket.end(), bucket.begin());
    for (auto it = source_last; --it != source_first - 1;)  // black magic
        dest_first[--bucket[radix_func(*it)]] = *it;
}

template <
    typename Iterator,
    typename value_type = typename std::iterator_traits<Iterator>::value_type>
inline void __do_final_rotation(Iterator first,
                                Iterator last,
                                std::false_type /* value_type is unsigned */) {}

template <
    typename Iterator,
    typename value_type = typename std::iterator_traits<Iterator>::value_type>
inline void __do_final_rotation(Iterator first,
                                Iterator last,
                                std::true_type /* value_type is signed */) {
    // In this case result will actually have the negative numbers at the
    // end (since they have larger values when converted to unsigned).
    // Therefore we have to "rotate" that negative part to the front.
    auto first_negative =
        std::find_if(first, last, [](value_type x) { return x < 0; });
    std::rotate(first, first_negative, last);
}

template <
    std::size_t _Radix,
    std::size_t _Bucket_size = (1UL << _Radix),
    typename Iterator,
    typename value_type = typename std::iterator_traits<Iterator>::value_type,
    std::size_t type_width = sizeof(value_type) * 8U>
inline void __radix_sort(Iterator first, Iterator last) {
    std::vector<value_type> tmp(std::distance(first, last));
    std::size_t offset = 0;
    while (offset < type_width) {
        __do_bucket_sort<_Bucket_size>(first, last, tmp.begin(), offset);
        __do_bucket_sort<_Bucket_size>(tmp.begin(), tmp.end(), first,
                                       offset + _Radix);
        offset += _Radix * 2;  // compiler knows
    }
    __do_final_rotation(first, last, std::is_signed<value_type>());
}

}  // namespace cpdsa

#endif  // RADIX_SORT_BASE_HPP