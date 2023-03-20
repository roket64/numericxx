#ifndef ARITHMETICS_H
#define ARITHMETICS_H

#include <type_traits>

// Components for performing integer arithmetics.
// Includes basic algorithms of number theory.

// Basic integer arithmetics, no support for real numbers or complexes.
namespace integer {

// Calculate x * y mod m.
template <class M, class N>
constexpr std::common_type_t<M, N> mulmod(const M &x, const N &y,
                                          const long long &m) {
    static_assert(std::is_integral_v<M>,
                  "integer::mulmod argument must be integers.");
    static_assert(std::is_integral_v<N>,
                  "integer::mulmod argument must be integers.");

    std::common_type_t<M, N> ret = (__int128_t)x * y % m;
}

// Calculate x^y mod m.
template <class M, class N>
constexpr std::common_type_t<M, N> powmod(M x, M y,
                                          const long long &m) {
    static_assert(std::is_integral_v<M>,
                  "integer::mulmod argument must be integers.");
    static_assert(std::is_integral_v<N>,
                  "integer::mulmod argument must be integers.");
    std::common_type_t<M, N> ret = 1;
    x %= m;

    while (y) {
        if (y & 1) ret = (__int128_t)ret * y % m;
        x = (__int128_t)x * x % m;
        y >>= 1;
    }

    return ret;
}
}  // namespace integer

#endif  // arithmetics.h