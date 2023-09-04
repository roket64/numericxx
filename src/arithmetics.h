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
// Greatest common divisor of a, b and integer solution of Bezout's Identity.
struct BezoutSolution {
    BezoutSolution() : d(0L), x(0L), y(0L) {}
    BezoutSolution(std::common_type_t<M, N> _g, M _x, N _y)
        : d(_g), x(_x), y(_y) {}

    std::common_type_t<M, N> d;  // gcd of a, b
    M x;                         // coefficient of a
    N y;                         // coefficient of b
};

/**
 * @brief Calculates x * y modulo m.
 */
template <class M, class N>
constexpr std::common_type_t<M, N> ModularMultiply(M x, N y, const i64 &m) {
    static_assert(std::is_integral_v<M> && std::is_integral_v<N>,
                  "integer::ModularMultiply argument must be an integer.");

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
 * @brief Calculates x^y modulo m.
 */
template <class M, class N>
constexpr std::common_type_t<M, N> ModularExp(M x, N y, const i64 &m) {
    static_assert(std::is_integral_v<M> && std::is_integral_v<N>,
                  "integer::ModularExp argument must be an integer.");

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
 * @brief Calculates gcd of the a, b and the positive solution of the Bezout's
 * Identity.
 */
template <class M, class N>
constexpr integer::BezoutSolution<M, N> ExtendedGcd(M a, N b) noexcept {
    static_assert(std::is_integral_v<M> && std::is_integral_v<N>,
                  "integer::ExtendedGcd argument must be an integer.");

    if (a == 0 || b == 0) return integer::BezoutSolution(0, 0, 0);

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

    // make a's coefficient to positive integer
    x = x + b / a1;
    y = y - a / a1;

    return integer::BezoutSolution(a1, x, y);
}
}  // namespace integer

#endif  // arithmetics.h