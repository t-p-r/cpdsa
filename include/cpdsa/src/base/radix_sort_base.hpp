/**
 * CPDSA: radix sort internal -*- C++ -*-
 *
 * @file include/cpdsa/src/base/radix_sort_base.hpp
 */

#ifndef RADIX_SORT_BASE_HPP
#define RADIX_SORT_BASE_HPP

#include <array>
#include <limits>
#include <numeric>
#include <type_traits>
#include <vector>

namespace cpdsa {

/**
 * @brief Bucket sort the sequence `[source_first, source_last)`, put result
 * in
 * `[dest_first, dest_first + source_last - source_first)`
 * @param offset this means that element X will be put into bucket number Y,
 * where Y is the number represented by bits `[offset, offset + _Radix]` (from
 * low to high) of X.
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
    auto radix_func = [offset](value_type s) {
        using unsigned_type = typename std::make_unsigned<value_type>::type;
        return ((static_cast<unsigned_type>(s) >> offset) & (_Bucket_size - 1));
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
inline typename std::enable_if<std::is_unsigned<value_type>::value, void>::type
__flip_sign_bit(Iterator first, Iterator last) {}

template <
    typename Iterator,
    typename value_type = typename std::iterator_traits<Iterator>::value_type>
inline typename std::enable_if<std::is_signed<value_type>::value, void>::type
__flip_sign_bit(Iterator first, Iterator last) {
    // In two's complement systems, since the highest bit for negative numbers
    // is 1, our radix sort algorithm would therefore put those numbers at the
    // top unless we do this hideous thing before and after it.
    for (auto it = first; it != last; ++it)
        *it ^= std::numeric_limits<value_type>::min();
}

template <
    std::size_t _Radix,
    std::size_t _Bucket_size = (1UL << _Radix),
    typename Iterator,
    typename value_type = typename std::iterator_traits<Iterator>::value_type,
    std::size_t type_width = sizeof(value_type) * 8U>
inline void __radix_sort(Iterator first, Iterator last) {
    __flip_sign_bit(first, last);
    std::vector<value_type> tmp(std::distance(first, last));
    std::size_t offset = 0;
    while (offset < type_width) {
        __do_bucket_sort<_Bucket_size>(first, last, tmp.begin(), offset);
        __do_bucket_sort<_Bucket_size>(tmp.begin(), tmp.end(), first,
                                       offset + _Radix);
        offset += _Radix * 2;  // compiler knows
    }
    __flip_sign_bit(first, last);
}

}  // namespace cpdsa

#endif  // RADIX_SORT_BASE_HPP