/**
 * CPDSA: Median heap implementation -*- C++ -*-
 *
 * @file src/median_heap.hpp
 */

#ifndef CPDSA_MEDIAN_HEAP
#define CPDSA_MEDIAN_HEAP

#if __cplusplus >= 202002L
#include <concepts>
#else
#include <type_traits>
#endif

#include <queue>

namespace cpdsa {

/**
 * @brief Types eligible to be elements of @c median_heap.
 *
 * @note Must be convertible to double because @c median() casts to that type.
 */
#if __cplusplus >= 202002L
template <typename _Tp>
concept Median_heap_element_type = std::three_way_comparable<_Tp> && std::convertible_to<_Tp, double>;
#endif

/**
 * @brief A standard container automatically maintaining its median.
 *
 * @tparam _Tp Type of element.
 *
 * @note The container employs two smaller containers @c lower_heap and
 * @c higher_heap such that the largest element in @c lower_heap does not
 * exceed the smallest element in @c higher_heap, and that the size of
 * @c lower_heap is either the same or exactly one less than that of
 * @c higher_heap.
 *
 * @note Because of this, the median of the entire container is either: the
 * largest element in @c lower_heap, the smallest element in @c higher_heap, or
 * the average of the two.
 *
 * @note The discrete median (with a container of size @a n, its @a (n+1)/2-th
 * largest element) is either the largest element in @c lower_heap or
 * the smallest element in @c higher_heap.
 *
 */
#if __cplusplus >= 202002L
template <Median_heap_element_type _Tp>
#else
template <typename _Tp>
#endif
class median_heap {
   private:
#if __cplusplus < 202002L  // C++11/14/17
    static_assert(std::is_convertible<_Tp, double>::value, "median heap element must be convertible to double");
    // TODO: assert <=>
#endif

    std::priority_queue<_Tp> lower_heap;
    std::priority_queue<_Tp, std::vector<_Tp>, std::greater<_Tp>> higher_heap;

    /**
     * @brief Maintain the size difference between the heaps.
     */
    void balance() {
        if (higher_heap.size() - 1 > lower_heap.size()) {
            lower_heap.push(higher_heap.top());
            higher_heap.pop();
        }
        if (lower_heap.size() > higher_heap.size()) {
            higher_heap.push(lower_heap.top());
            lower_heap.pop();
        }
    }

   public:
    /**
     *  @brief  Creates a median_heap with no elements.
     */
    median_heap() = default;

    ~median_heap() = default;

    /**
     *  @brief  Add data to the container.
     *  @param x Data to be added.
     */
    void push(const _Tp& x) {
        if (higher_heap.empty() || x >= higher_heap.top())
            higher_heap.push(x);
        else
            lower_heap.push(x);
        balance();
    }

    /**
     *  @brief Remove the discrete median of the container.
     */
    void pop() {
        if (lower_heap.size() == higher_heap.size())
            lower_heap.pop();
        else
            higher_heap.pop();
        balance();
    }

    /**
     *  @brief Remove all elements from the container.
     */
    void clear() {
        while (!lower_heap.empty()) lower_heap.pop();
        while (!higher_heap.empty()) higher_heap.pop();
    }

    /**
     *  @return The number of elements in the container.
     */
    [[nodiscard]] const std::size_t size() const { return lower_heap.size() + higher_heap.size(); }

    /**
     *  @return @a true if the container is empty.
     */
    [[nodiscard]] const bool empty() const { return lower_heap.empty() && higher_heap.empty(); }

    /**
     * @return The discrete median (with a container of size @a n, its
     * @a (n+1)/2-th largest element) of the container.
     */
    [[nodiscard]] const _Tp& discrete_median() const {
        if (lower_heap.size() == higher_heap.size()) return lower_heap.top();
        return higher_heap.top();
    }

    /**
     *  @return The median of the container.
     */
    [[nodiscard]] const double median() const {
        if (lower_heap.size() == higher_heap.size()) return 1.0 * (lower_heap.top() + higher_heap.top()) / 2;
        return higher_heap.top();
    }
};
}  // namespace cpdsa

#endif /* CPDSA_MEDIAN_HEAP */