// Median heap implementation -*- C++ -*-

#ifndef CPDSA_MEDIAN_HEAP
#define CPDSA_MEDIAN_HEAP

#include <queue>
#include <vector>

namespace cpdsa {
/**
 * @brief A standard container automatically maintaining its median.
 *
 *
 * @tparam _Tp Type of element.
 *
 * @note The container employs two smaller containers @c lower_heap and
 * @c higher_heap, where the largest elements in @c lower_heap does not exceed
 * the smallest element in @c higher_heap, and the size of @c lower_heap is
 * either the same or exactly one less than that of @c higher_heap.
 *
 * @note In this manner, the median is either: the largest element in
 * @c lower_heap, the smallest element in @c higher_heap, or the average of
 * the two.
 *
 * @note The discrete median (with a container of size @c n, its (n+1)/2-th
 * largest element) is either the largest element in @c lower_heap or
 * the smallest element in @c higher_heap,
 */
template <typename _Tp>
struct median_heap {
   private:
    std::priority_queue<_Tp> lower_heap;
    std::priority_queue<_Tp, std::vector<_Tp>, std::greater<_Tp>> higher_heap;

    void balance();

   public:
    /**
     *  @brief  Creates a median_heap with no elements.
     */
    median_heap() = default;

    ~median_heap() = default;

    /**
     *  @brief  Add data to the container.
     *  @param __x Data to be added.
     */
    void push(const _Tp& __x);

    /**
     *  @brief  Returns the discrete median (with a container of size @c n, its
     * (n+1)/2-th largest element) of the container.
     */
    [[nodiscard]] constexpr _Tp discrete_median() const;

    /**
     *  @brief  Remove the discrete median of the container.
     */
    void pop();

    /**
     *  @brief  Returns the number of elements in the container.
     */
    [[nodiscard]] constexpr size_t size() const;

    /**
     *  @brief  Returns true if the container is empty.
     */
    [[nodiscard]] constexpr bool empty() const;

    /**
     *  @brief  Remove all elements from the container.
     */
    void clear();

    /**
     *  @brief  Returns the median of the container.
     */
    [[nodiscard]] constexpr double median() const;
};
}  // namespace cpdsa

#endif /* CPDSA_MEDIAN_HEAP */