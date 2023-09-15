#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <cmath>
#include <tuple>
#include <type_traits>

#include "configs/config.h"
#include "exceptions.h"
#include "utilities.h"

namespace numericxx {
template <class M, class N>
class BezoutIdentity {
   public:
    BezoutIdentity() : d(0), x(0), y(0){};
    BezoutIdentity(std::common_type_t<M, N> _g, M _x, N _y)
        : d(_g), x(_x), y(_y){};

    /* Greatest Common Divisor of a, b */
    std::common_type_t<M, N> d;
    /* Coefficient of a */
    M x;
    /* Coefficient of b */
    N y;
};

/**
 * @brief Binary Euclidean Algorithm
 * @details Returns GCD of a, b
 */
template <class M, class N>
constexpr std::common_type_t<M, N> Gcd(M a, N b) noexcept {
    if (a == 0 || b == 0) return 0;

    std::common_type_t<M, N> d = 1;

    /* Remove powers of two from GCD */
    while (a % 2 == 0 && b % 2 == 0) {
        a /= 2;
        b /= 2;
        d *= 2;
    }

    /* At least one of them is now odd */
    while (a != 0) {
        while (a % 2 == 0) a /= 2;
        while (b % 2 == 0) b /= 2;

        /* Now both a and b are odd */
        if (a >= b)
            a = (a - b) / 2;
        else
            b = (b - a) / 2;
    }

    return d * b;
}

/**
 * @brief Extended Euclidean Algorithm
 * @details Returns GCD of a, b and coefficients of Bezout's identity
 */
template <class M, class N>
constexpr numericxx::BezoutIdentity<M, N> ExtendedGcd(M a, N b) noexcept {
    static_assert(std::is_integral_v<M> && std::is_integral_v<N>,
                  "numericxx::ExtendedGcd argument must be integers.");

    using CommonType = std::common_type_t<M, N>;

    const CommonType abs_a = numericxx::Abs<CommonType>(a);
    const CommonType abs_b = numericxx::Abs<CommonType>(b);

    M x = 1, x1 = 0;
    N y = 0, y1 = 1;

    CommonType a1 = a, b1 = b;

    while (b1) {
        CommonType q = a1 / b1;
        std::tie(x, x1) = std::make_pair(x1, x - q * x1);
        std::tie(y, y1) = std::make_pair(y1, y - q * y1);
        std::tie(a1, b1) = std::make_pair(b1, a1 - q * b1);
    }

    x = x + b / a1;
    y = y - a / a1;

    numericxx::BezoutIdentity<M, N> ret(a1, x, y);
    return ret;
}
};  // namespace numericxx

#endif  // algorithms.h