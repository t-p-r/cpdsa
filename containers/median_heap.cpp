#include "median_heap.hpp"

namespace cpdsa {

/**
 * @brief Balance the sizes of @c lower_heap and
 * @c higher_heap, so as to maintain the size restriction described above.
 */
template <typename _Tp>
void median_heap<_Tp>::balance() {
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

template <typename _Tp>
void median_heap<_Tp>::push(const _Tp& __x) {
    if (higher_heap.empty() || __x >= higher_heap.top())
        higher_heap.push(__x);
    else
        lower_heap.push(__x);
    balance();
}

template <typename _Tp>
[[nodiscard]] constexpr _Tp median_heap<_Tp>::discrete_median() const {
    if (lower_heap.size() == higher_heap.size())
        return lower_heap.top();
    return higher_heap.top();
}

template <typename _Tp>
[[nodiscard]] constexpr size_t median_heap<_Tp>::size() const {
    return lower_heap.size() + higher_heap.size();
}

template <typename _Tp>
[[nodiscard]] constexpr bool median_heap<_Tp>::empty() const {
    return !size();
}

template <typename _Tp>
void median_heap<_Tp>::pop() {
    if (lower_heap.size() == higher_heap.size())
        lower_heap.pop();
    else
        higher_heap.pop();
    balance();
}

template <typename _Tp>
void median_heap<_Tp>::clear() {
    while (!lower_heap.empty())
        lower_heap.pop();
    while (!higher_heap.empty())
        higher_heap.pop();
}

template <typename _Tp>
[[nodiscard]] constexpr double median_heap<_Tp>::median() const {
    if (lower_heap.size() == higher_heap.size())
        return 1.0 * (lower_heap.top() + higher_heap.top()) / 2;
    return higher_heap.top();
}
}  // namespace cpdsa