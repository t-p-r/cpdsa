/**
 * CPDSA: Ordered set -*- C++ -*-
 * 
 * @file src/ordered_set.hpp
 */

#ifndef CPDSA_ORDERED_SET
#define CPDSA_ORDERED_SET

#include <limits>

#include "base/ordered_set_base.hpp"

namespace cpdsa {
/**
 * @brief A container allowing for operations on discrete values in logarithmic
 * time.
 *
 * @tparam _Tp Type of element. Must be discrete (i.e. @c std::integral<_Tp>
 * must holds true).
 * @tparam LB The smallest value allowed to be added.
 * @tparam RB One past the largest value allowed to be added.
 *
 * @note An implementation of a dynamic segment tree. Operations
 * have time complexity @a O(log(X)) where @a X = @a RB - @a LB. @a LB and @a RB
 * must be specified if @c std::numeric_limits<_Tp> is not provided.
 */
template <std::integral _Tp, _Tp LB = std::numeric_limits<_Tp>::min(),
          _Tp RB = std::numeric_limits<_Tp>::max()>
class ordered_set : private ordered_set_base<_Tp, LB, RB> {
   private:
    using Base_type = ordered_set_base<_Tp, LB, RB>;

   public:
    /**
     * @brief Create an ordered_set with no elements.
     */
    ordered_set() = default;

    /**
     * @brief Returns one past the largest number allowed to be added.
     */
    [[nodiscard]] constexpr _Tp end() const noexcept { return RB; }

    /**
     * @brief Returns the number of elements in the container.
     */
    [[nodiscard]] constexpr size_t size() const noexcept {
        return this->root->cnt;
    }

    /**
     * @brief Returns true if the container is empty.
     */
    [[nodiscard]] constexpr bool empty() const noexcept { return !size(); }

    /**
     * @brief Add a new element into the container.
     *
     * @param val Value to be added.
     */
    constexpr void insert(const _Tp& val) {
        Base_type::update(*(this->root), LB, RB, val,
                          Base_type::NODE_UPDATE_ACTIONS::ADD_ONCE);
    }

    /**
     * @brief Remove one occurence of `val` from the
     * container.
     *
     * @param val Value to be removed.
     */
    constexpr void erase_once(const _Tp& val) {
        Base_type::update(*(this->root), LB, RB, val,
                          Base_type::NODE_UPDATE_ACTIONS::REMOVE_ONCE);
    }

    /**
     * @brief Remove all occurences of `val` from the container.
     *
     * @param val Value to be removed.
     */
    constexpr void erase_all(const _Tp& val) {
        Base_type::update(*(this->root), LB, RB, val,
                          Base_type::NODE_UPDATE_ACTIONS::REMOVE_ALL);
    }

    /**
     * @brief Remove all elements from the container.
     */
    void clear() { this = new ordered_set(); }

    /**
     * @brief Returns the number of elements in the range `[l,r]`.
     *
     */
    [[nodiscard]] constexpr int count(_Tp l, _Tp r) const noexcept {
        return Base_type::get(*(this->root), LB, RB, l, r);
    }

    /**
     * @brief Returns the number of elements less than or equal to @c val.
     */
    [[nodiscard]] constexpr int order_of_key(const _Tp& val) const noexcept {
        return Base_type::get(*(this->root), LB, RB, LB, val);
    }

    /**
     * @brief Returns the k-th (1-based) largest element in the container.
     *
     * @param k The position of the element to find.
     *
     * @return Either said value or RB if no such value exists.
     */
    [[nodiscard]] constexpr _Tp find_by_order(const size_t& k) const noexcept {
        if (size() >= k)
            return Base_type::k_largest(*(this->root), LB, RB, k);
        else
            return RB;
    }

    /**
     * @brief Returns the smallest value in the container no less than @c val.
     *
     * @return Either said value or RB if no such value exists.
     */
    [[nodiscard]] constexpr _Tp lower_bound(const _Tp& val) const noexcept {
        return Base_type::lower_bound(*(this->root), LB, RB, val);
    }

    /**
     * @brief Returns the largest value in the container no more than @c val.
     *
     * @return Either said value or RB if no such value exists.
     */
    [[nodiscard]] constexpr _Tp upper_bound(const _Tp& val) const noexcept {
        return Base_type::upper_bound(*(this->root), LB, RB, val);
    }
};
}  // namespace cpdsa

#endif /* CPDSA_ORDERED_SET */