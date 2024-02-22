// Ordered set implementation -*- C++ -*-
#include <memory>
#include <numeric>  // for std::midpoint

#ifndef CPDSA_ORDERED_SET_BASE
#define CPDSA_ORDERED_SET_BASE

namespace cpdsa {
/**
 * @brief Background implementation for ordered_set.
 */
template <typename _Tp, _Tp LB, _Tp RB>
class ordered_set_base {
   private:
    static const int NULL_NODE_COUNT = 0;
    static const int NULL_NODE_SUM = 0;
    static const int NULL_NODE_MAX = LB;
    static const int NULL_NODE_MIN = RB;

    /**
     * @brief Node implementation.
     */
    struct node {
        int cnt;            // the amount of elements currently in the node ...
        _Tp sum;            // ... and their sum.
        _Tp lowest_value;   // Value bounds for the node.
        _Tp highest_value;  // An uninstantiated or null node has
                            // lowest_value = RB and highest_value = LB.
        std::shared_ptr<node> left_child;
        std::shared_ptr<node> right_child;  // left and right child

        node()
            : cnt(NULL_NODE_COUNT),
              sum(NULL_NODE_SUM),
              lowest_value(NULL_NODE_MIN),
              highest_value(NULL_NODE_MAX) {}

        /**
         * @brief Returns whether the current node doesn't overlap with the
         * range
         * ```[u,v]```
         */
        bool out_of_bound(_Tp u, _Tp v) const noexcept {
            return (highest_value < u || v < lowest_value);
        }

        /**
         * @brief Returns whether the current node is completely within the
         * range
         * ```[u,v]```
         */
        bool contained_by(_Tp u, _Tp v) const noexcept {
            return (u <= lowest_value && lowest_value <= v);
        }
    };

#define NULL_NODE nullptr

   protected:
    static constexpr int ADD_ONCE = 0;
    static constexpr int REMOVE_ONCE = 1;
    static constexpr int REMOVE_ALL =
        2;  // these should have been an enum but
            // are also used by child classes so ...
    enum NODE_DIRECTIONS { LEFT, RIGHT };

    std::shared_ptr<node> root;

    explicit ordered_set_base() : root(new node()) {
        static_assert(std::is_integral<_Tp>());
    }

    /**
     * @brief Creates a new node and attaches it to the parent node in the given
     * direction.
     *
     * @param __par The parent node.
     * @param __dir The direction in which to attach the new node (0 for left
     * child, 1 for right child).
     */
    constexpr void create_node(std::shared_ptr<node> par, bool dir) {
        if (dir == NODE_DIRECTIONS::LEFT)
            par->left_child = std::shared_ptr<node>(new node());
        else
            par->right_child = std::shared_ptr<node>(new node());
    }

    /**
     * @brief Wrapper function for cnt
     */
    [[nodiscard]] constexpr _Tp get_cnt(
        std::shared_ptr<node> id) const noexcept {
        return id == NULL_NODE ? NULL_NODE_COUNT : id->cnt;
    }

    /**
     * @brief Wrapper function for sum.
     */
    [[nodiscard]] constexpr _Tp get_sum(
        std::shared_ptr<node> id) const noexcept {
        return id == NULL_NODE ? NULL_NODE_SUM : id->sum;
    }

    /**
     * @brief Wrapper function for lowest_value.
     */
    [[nodiscard]] constexpr _Tp get_lowest(
        std::shared_ptr<node> id) const noexcept {
        return id == NULL_NODE ? RB : id->lowest_value;
    }

    /**
     * @brief Wrapper function for highest_value.
     */
    [[nodiscard]] constexpr _Tp get_highest(
        std::shared_ptr<node> id) const noexcept {
        return id == NULL_NODE ? LB : id->highest_value;
    }

    /**
     * @brief Update the state of a leaf value/node in the container.
     *
     * @param leaf The current node.
     * @param val Value being updated.
     * @param action Action specified (see @c NODE_UPDATE_ACTIONS)
     */
    constexpr void update_leaf(std::shared_ptr<node> leaf, _Tp val, int action) {
        if (leaf->cnt == 0 && (action == REMOVE_ONCE || action == REMOVE_ALL))
            return;

        switch (action) {
            case ADD_ONCE:
                leaf->cnt++;
                leaf->sum += val;
                break;
            case REMOVE_ONCE:
                leaf->cnt--;
                leaf->sum -= val;
                break;
            case REMOVE_ALL:
                leaf->cnt = leaf->sum = 0;
                break;
            default:
                break;
        }

        leaf->lowest_value = leaf->cnt ? val : RB;
        leaf->highest_value = leaf->cnt ? val : LB;
    }

    /**
     * @brief Update values of the current node by propagating from its childs.
     *
     * @param id The current node.
     */
    constexpr void update_from_childs(std::shared_ptr<node> id) {
        id->cnt = get_cnt(id->left_child) + get_cnt(id->right_child);
        id->sum = get_sum(id->left_child) + get_sum(id->right_child);
        id->lowest_value =
            std::min(get_lowest(id->left_child), get_lowest(id->right_child));
        id->highest_value =
            std::max(get_highest(id->left_child), get_highest(id->right_child));
    }

    /**
     * @brief Recursively update the state of a node, and all its descendants
     * containing @c val in the container.
     *
     * @param id The current node.
     * @param l Left boundary of the node's range.
     * @param r Right boundary of the node's range.
     * @param val Value being updated.
     * @param action Action specified (see @c NODE_UPDATE_ACTIONS)
     *
     * @note In effect, the value of the leaf node containing @c val will have
     * its values modifies first, followed by its ancestor nodes through
     * ```update_from_childs```.
     *
     */
    void update(std::shared_ptr<node> id, _Tp l, _Tp r, _Tp val, int action) {
        if (l == r) {
            update_leaf(id, val, action);
            return;
        }

        _Tp mid = std::midpoint(l, r);
        if (val <= mid) {
            if (id->left_child == NULL_NODE)
                create_node(id, NODE_DIRECTIONS::LEFT);
            update(id->left_child, l, mid, val, action);
        } else {
            if (id->right_child == NULL_NODE)
                create_node(id, NODE_DIRECTIONS::RIGHT);
            update(id->right_child, mid + 1, r, val, action);
        }

        update_from_childs(id);
    }

    /**
     * @brief Returns the sum of values stored in the range of a given node.
     *
     * @param id The current node.
     * @param l Left boundary of the node's range.
     * @param r Right boundary of the node's range.
     * @param u Left boundary of the query range.
     * @param v Right boundary of the query range.
     */
    [[nodiscard]] _Tp get(std::shared_ptr<node> id,
                          _Tp l,
                          _Tp r,
                          _Tp u,
                          _Tp v) const {
        if (id == NULL_NODE || id.out_of_bound(u, v))
            return NULL_NODE_SUM;
        if (id.contained_by(u, v))
            return get_cnt(id);
        _Tp mid = std::midpoint(l, r);
        return get(id->left_child, l, mid, u, v) +
               get(id->right_child, mid + 1, r, u, v);
    }

    /**
     * @brief Find the value of the k-th largest (1-based) element in the given
     * node
     *
     * @param id The current node.
     * @param l Left boundary of the node's range.
     * @param r Right boundary of the node's range.
     * @param k The position to find.
     *
     * @return Either said value or RB if no such value exists.
     */
    [[nodiscard]] _Tp k_largest(std::shared_ptr<node> id,
                                _Tp l,
                                _Tp r,
                                int k) const {
        if (id == NULL_NODE)
            return RB;
        if (l == r)
            return id->cnt ? id->lowest_value : RB;

        _Tp mid = std::midpoint(l, r);

        if (get_cnt(id->left_child) >= k)
            return k_largest(id->left_child, l, mid, k);
        else
            return k_largest(id->right_child, mid + 1, r,
                             k - get_cnt(id->left_child));
    }

    /**
     * @brief Find the smallest value in a node not less than @c val.
     *
     * @param id The current node.
     * @param l Left boundary of the node's range.
     * @param r Right boundary of the node's range.
     * @param val Value to compare against.
     *
     * @return Either said value or RB if no such value exists.
     */
    [[nodiscard]] _Tp lower_bound(std::shared_ptr<node> id,
                                  _Tp l,
                                  _Tp r,
                                  _Tp val) const {
        if (id == NULL_NODE)
            return RB;
        if (l == r)
            return id->cnt ? id->lowest_value : RB;
        _Tp mid = std::midpoint(l, r);

        if (id->left_child != NULL_NODE && get_highest(id->left_child) >= val)
            return lower_bound(id->left_child, l, mid, val);
        else
            return lower_bound(id->right_child, mid + 1, r, val);
    }

    /**
     * @brief Find the largest value in a node not more than @c val.
     *
     * @param id The current node.
     * @param l Left boundary of the node's range.
     * @param r Right boundary of the node's range.
     * @param val Value to compare against.
     *
     * @return Either said value or RB if no such value exists.
     */
    [[nodiscard]] _Tp upper_bound(std::shared_ptr<node> id,
                                  _Tp l,
                                  _Tp r,
                                  _Tp val) const {
        if (id == NULL_NODE)
            return RB;
        if (l == r)
            return id->cnt ? id->lowest_value : RB;

        _Tp mid = std::midpoint(l, r);
        if (id->right_child != NULL_NODE && get_lowest(id->right_child) <= val)
            return upper_bound(id->right_child, mid + 1, r, val);
        else
            return upper_bound(id->left_child, l, mid, val);
    }
};

#undef NULL_NODE
}  // namespace cpdsa

#endif /* CPDSA_ORDERED_SET_BASE */