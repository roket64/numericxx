#ifndef CONGRUENCE_H
#define CONGRUENCE_H

#include <vector>

#include "basic_arithmetics.h"
#include "exceptions.h"

// Basic congruence operations

namespace integer {
namespace congruence {
/**
 *  @brief Solve congruence ax = b (mod m) for all possible x.
 *  @param a An integer from ax = b (mod m)
 *  @param b An integer from ax = b (mod m)
 *  @param m A modular value from ax = b (mod m)
 */
template <class M, class N, class T>
constexpr std::vector<std::common_type_t<M, N>> SolveCongruence(const M &a, const N &b, const T &m) {
    static_assert(std::is_integral_v<M> && std::is_integral_v<N>,
                  "integer::congruence::SolveCongruence argument must be integers.");
    static_assert(std::is_integral_v<T>,
                  "integer::congruence::SolveCongruence argument must be integers.");

    std::vector<std::common_type_t<M, N>> ret;

    auto [g, u, v] = integer::ExtendedGcd(a, m);

    if (b % g)
        throw exceptions::InvalidSolutionException(
            "There is no possible solution of given congruence.");

    std::common_type_t<M, N> x0 = u * b / g;

    for (int i = 0; i < g; ++i) {
        ret.push_back(x0);
        x0 += m / g;
        x0 %= m;
    }

    return ret;
}
}  // namespace congruence
}  // namespace integer

#endif  // congruence.h