/**
 * CPDSA: Skip list, base implementation -*- C++ -*-
 *
 * @file include/cpdsa/src/base/skip_list_base.hpp
 */

#ifndef CPDSA_SKIP_LIST_BASE
#define CPDSA_SKIP_LIST_BASE

#include <cstddef>
#include <list>

namespace cpdsa {

/**
 * @brief Background implementation for skip_list.
 *
 * @note Todo after first-working-iteration: contiguous blocks _Tp[] totaling 64 bytes.
 */
template <typename _Tp, std::size_t _Levels = 16>
class skip_list_base {
   private:
    std::list<_Tp> levels[_Levels];

   protected:
};

}  // namespace cpdsa

#endif /* CPDSA_SKIP_LIST_BASE */
