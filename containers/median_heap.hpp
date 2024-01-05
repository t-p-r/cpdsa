// Median heap implementation -*- C++ -*-

#include <queue>
#include <vector>

/**
 * @brief A standard container automatically maintaining its median.
 *
 * @ingroup sequences
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

    /**
     * @brief Balance the sizes of @c lower_heap and
     * @c higher_heap, so as to maintain the size restriction described above.
     */
    void balance() {
        if (higher_heap.size() - 1 > lower_heap.size()) {
            int __x = higher_heap.top();
            higher_heap.pop();
            lower_heap.push(__x);
        }
        if (lower_heap.size() > higher_heap.size()) {
            int __x = lower_heap.top();
            lower_heap.pop();
            higher_heap.push(__x);
        }
    }

   public:
    /**
     *  @brief  Creates a median_heap with no elements.
     */
    median_heap() : lower_heap(), higher_heap() {}

    /**
     *  @brief  Add data to the container.
     *  @param __x Data to be added.
     */
    void push(_Tp __x) {
        if (higher_heap.empty() || __x >= higher_heap.top())
            higher_heap.push(__x);
        else
            lower_heap.push(__x);
        balance();
    }

    /**
     *  @brief  Returns the discrete median (with a container of size @c n, its
     * (n+1)/2-th largest element) of the container.
     */
    _Tp discrete_median() {
        if (lower_heap.size() == higher_heap.size())
            return lower_heap.top();
        return higher_heap.top();
    }

    /**
     *  @brief  Remove the discrete median of the container.
     */
    void pop() {
        if (lower_heap.size() == higher_heap.size())
            lower_heap.pop();
        else
            higher_heap.pop();
        balance();
    }

    /**
     *  @brief  Returns the number of elements in the container.
     */
    size_t size() const { return lower_heap.size() + higher_heap.size(); }

    /**
     *  @brief  Returns true if the container is empty.
     */
    bool empty() const { return !size(); }

    /**
     *  @brief  Remove all elements from the container.
     */
    void clear() {
        while (!lower_heap.empty())
            lower_heap.pop();
        while (!higher_heap.empty())
            higher_heap.pop();
    }

    /**
     *  @brief  Returns the median of the container.
     */
    double median() {
        if (lower_heap.size() == higher_heap.size())
            return 1.0 * (lower_heap.top() + higher_heap.top()) / 2;
        return higher_heap.top();
    }
};