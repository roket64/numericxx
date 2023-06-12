#ifndef CONGRUENCE_H
#define CONGRUENCE_H

#include <type_traits>

#include "basic_arithmetics.h"

// Basic congruence operations

namespace integer {
    /**
     *  @brief Solve congruence ax = b (mod m) of x.
    */
template <class M, class N>
constexpr std::common_type_t<M, N> solve(M a, N b, const long long &m) {
    static_assert(std::is_integral_v<M>,
                  "integer::solve argument must be integers.");
    static_assert(std::is_integral_v<N>,
                  "integer::solve argument must be integers.");

    auto [g, u, v] = integer::gcd(a, m);
    if (b % g) return 0;

    return u * b / g;
}

}  // namespace integer

#endif  // congruence.h