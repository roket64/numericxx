#ifndef ARITHMETICS_H
#define ARITHMETICS_H

#include <cmath>
#include <tuple>
#include <type_traits>

#include "exceptions.h"
#include "int_types.h"

// Components for performing integer arithmetics.
// Includes basic algorithms of number theory.

// Basic integer arithmetics, no support for real numbers or complexes.
namespace integer {
template <class M, class N>
// Struct for gcd(a, b) and the coefficient of bezout's identity.
struct solution {
    solution() : g(0), x(0), y(0) {}
    solution(std::common_type_t<M, N> _g, M _x, N _y) : g(_g), x(_x), y(_y) {}

    std::common_type_t<M, N> g;  // gcd of a, b
    M x;                         // coefficient of a
    N y;                         // coefficient of b
};

/**
 * @brief Calculate x * y (mod m)
 */
template <class M, class N>
constexpr std::common_type_t<M, N> mulmod(M x, N y, const i64 &m) {
    static_assert(std::is_integral_v<M> && std::is_integral_v<N>,
                  "integer::mulmod argument must be an integer.");

    if (m == 0)
        throw exceptions::DividedByZeroException(
            "modulo value must be not a zero.");

    std::common_type_t<M, N> ret = 0;

    while (y) {
        if (y & 1) ret = (i128)(ret + x) % m;
        x = (i128)2 * x % m;
        y >>= (N)1;
    }

    return ret;
}

/**
 * @brief Calculate x^y (mod m)
 */
template <class M, class N>
constexpr std::common_type_t<M, N> powmod(M x, N y, const i64 &m) {
    static_assert(std::is_integral_v<M> && std::is_integral_v<N>,
                  "integer::powmod argument must be an integer.");

    if (m == 0)
        throw exceptions::DividedByZeroException(
            "modulo value must be not a zero.");

    std::common_type_t<M, N> ret = 1;
    x %= m;

    while (y) {
        if (y & 1) ret = (i128)ret * x % m;
        x = (i128)x * x % m;
        y >>= (N)1;
    }

    return ret;
}

/**
 * @brief Calculate gcd of the given a, b and the coefficient of the Bezout's
 * Identity
 */
template <class M, class N>
constexpr integer::solution<M, N> gcd(M a, N b) noexcept {
    static_assert(std::is_integral_v<M> && std::is_integral_v<N>,
                  "integer::gcd argument must be an integer.");

    if (a == 0 || b == 0)
        return integer::solution(0, 0, 0);

    a = std::abs(a);
    b = std::abs(b);

    M x = 1, x1 = 0;
    N y = 0, y1 = 1;

    std::common_type_t<M, N> a1 = a, b1 = b;

    while (b1) {
        std::common_type_t<M, N> q = a1 / b1;
        std::tie(x, x1) = std::make_tuple(x1, x - q * x1);
        std::tie(y, y1) = std::make_tuple(y1, y - q * y1);
        std::tie(a1, b1) = std::make_tuple(b1, a1 - q * b1);
    }

    // positive coefficient of a
    x = x + b / a1;
    y = y - a / a1;

    return integer::solution(a1, x, y);
}
}  // namespace integer

#endif  // arithmetics.h