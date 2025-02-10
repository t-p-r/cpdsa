/**
 * CPDSA: 32-bit radix sort -*- C++ -*-
 *
 * @file src/radix_sort_32.hpp
 */

#ifndef CPDSA_RADIX_SORT_32_HPP
#define CPDSA_RADIX_SORT_32_HPP

#include <algorithm>
#include <array>
#include <concepts>
#include <cstdint>
#include <iterator>
#include <type_traits>
#include <vector>

namespace cpdsa {

#if __cplusplus >= 202002L
template <typename Iterator>
concept RAIterator32 = std::random_access_iterator<Iterator> && requires {
    sizeof(typename std::iterator_traits<Iterator>::value_type) <= 4;
};
template <typename Iterator>
concept RAIterator64 = std::random_access_iterator<Iterator> && requires {
    sizeof(typename std::iterator_traits<Iterator>::value_type) == 8;
};
#endif

/**
 * @brief Stably sort a range [begin, end) of 32-bit (or narrower) integers.
 * @note Implement an algorithm roughly similar to the one used in building
 * suffix arrays.
 */
#if __cplusplus >= 202002L
template <RAIterator32 Iterator>
#else
template <typename Iterator>
#endif
void radix_sort_32(Iterator begin, Iterator end) {
    using value_type = typename std::iterator_traits<Iterator>::value_type;

#if __cplusplus < 202002L
    static_assert(sizeof(typename std::iterator_traits<Iterator>::value_type) <=
                      4;
                  "elements must be 32-bit (or narrower) integers");
    static_assert(
        std::is_base_of<
            std::random_access_iterator_tag,
            typename std::iterator_traits<Iterator>::iterator_category>::value,
        "begin and end require random access iterators");
#endif

    if (begin == end)
        return;

    static constexpr int HALF_32BIT = 16;
    static constexpr int BUCKET_SIZE = 1 << HALF_32BIT;

    // bits 31 -> 16, auto convert to unsigned
    static auto upper_half = [](uint32_t s) { return (s >> HALF_32BIT); };
    // bits 15 -> 0, auto convert to unsigned
    static auto lower_half = [](uint32_t s) { return (s & (BUCKET_SIZE - 1)); };

    const size_t N_elem = std::distance(begin, end);

    // used to pigeonhole elements based on their upper/lower half
    // note: add 256-512KB to stack
    std::array<size_t, BUCKET_SIZE> bucket;

    // manual allocation is about 3-5% faster than using a vector
    std::vector<size_t> sorted_by_lower_half(N_elem);

    // FIRST ITERATION: sort by lower half ------------------------------------
    // lesson learnt: turns out fill() can decay to memset
    bucket.fill(0);

    for (auto it = begin; it != end; ++it)
        bucket[lower_half(*it)]++;

    std::partial_sum(bucket.begin(), bucket.end(), bucket.begin());

    for (size_t i = 0; i < N_elem; ++i)
        sorted_by_lower_half[--bucket[lower_half(begin[i])]] = begin[i];

    // SECOND ITERATION: sort by upper half -----------------------------------
    bucket.fill(0);

    for (auto it = begin; it != end; ++it)
        bucket[upper_half(*it)]++;

    std::partial_sum(bucket.begin(), bucket.end(), bucket.begin());

    for (auto it = sorted_by_lower_half.rbegin();
         it != sorted_by_lower_half.rend(); ++it) {
        begin[--bucket[upper_half(*it)]] = *it;
    }

#if __cplusplus >= 201703L
    if constexpr (std::is_signed<value_type>::value) {
#else
    if (std::is_signed<value_type>::value) {
#endif
        // In this case result will actually have the negative numbers at the
        // end (since they have larger values when converted to unsigned).
        // Therefore we have to "rotate" that negative part to the front.
        auto first_negative =
            std::find_if(begin, end, [](value_type x) { return x < 0; });
        std::rotate(begin, first_negative, end);
    }
}

}  // namespace cpdsa

#endif /* CPDSA_RADIX_SORT_32_HPP */