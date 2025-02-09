/**
 * CPDSA: 32-bit radix sort -*- C++ -*-
 *
 * @file src/radix_sort_32.hpp
 */

#ifndef CPDSA_RADIX_SORT_32_HPP
#define CPDSA_RADIX_SORT_32_HPP

#include <algorithm>
#include <array>
#include <cstdint>
#include <iterator>
#include <type_traits>
#include <vector>

namespace cpdsa {

/**
 * @brief Radix sort a range [begin, end) of 32-bit integers.
 */
template <typename Iterator>
void radix_sort_32(Iterator begin, Iterator end) {
    using value_type = typename std::remove_reference<decltype(*begin)>::type;

    static_assert(std::is_same<value_type, int32_t>::value ||
                      std::is_same<value_type, uint32_t>::value,
                  "elements must be 32-bit integers");
    static_assert(
        std::is_base_of<
            std::random_access_iterator_tag,
            typename std::iterator_traits<Iterator>::iterator_category>::value,
        "begin and end require random access iterators");

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
    // note: add 262KB to stack
    std::array<size_t, BUCKET_SIZE> bucket;

    // manual allocation is about 3-5% faster than using a vector
    std::vector<size_t> lower_half_order(N_elem);

    // FIRST ITERATION: sort by lower half ------------------------------------
    // lesson learnt: turns out fill() can decay to memset
    bucket.fill(0);

    for (auto it = begin; it != end; ++it)
        bucket[lower_half(*it)]++;

    for (size_t i = 1; i < (BUCKET_SIZE); i++)
        bucket[i] += bucket[i - 1];

    for (size_t i = 0; i < N_elem; ++i)
        lower_half_order[--bucket[lower_half(begin[i])]] = i;

    // SECOND ITERATION: sort by upper half -----------------------------------
    bucket.fill(0);

    for (auto it = begin; it != end; ++it)
        bucket[upper_half(*it)]++;

    for (size_t i = 1; i < (BUCKET_SIZE); i++)
        bucket[i] += bucket[i - 1];

    std::vector<uint32_t> result(N_elem);

    for (auto it = lower_half_order.rbegin(); it != lower_half_order.rend();
         ++it) {
        auto elem = begin[*it];
        result[--bucket[upper_half(elem)]] = elem;
    }

    // Final copy back to [begin, end)
#if __cplusplus >= 201703L
    if constexpr (std::is_signed<value_type>::value) {
#else
    if (std::is_signed<value_type>::value) {
#endif
        // In this case result will actually have the negative numbers at the
        // end (since they have larger values when converted to unsigned).
        // Therefore we have to "rotate" that negative part to the front.
        auto first_negative = result.begin();
        while (first_negative != result.end() &&
               static_cast<int32_t>(*first_negative) >= 0)
            first_negative++;
        std::rotate(result.begin(), first_negative, result.end());
    }

    std::copy(result.begin(), result.end(), begin);
}

} // namespace cpdsa

#endif // CPDSA_RADIX_SORT_32_HPP