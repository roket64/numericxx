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
class Solution {
   public:
    Solution() : d(0), x(0), y(0) {}
    Solution(std::common_type_t<M, N> _g, M _x, N _y) : d(_g), x(_x), y(_y) {}

    std::common_type_t<M, N> d;  // gcd of a, b
    M x;                         // coefficient of a
    N y;                         // coefficient of b
};

template <class M, class N>
constexpr numericxx::Solution<M, N> Gcd(M a, N b) noexcept {
    static_assert(std::is_integral_v<M> && std::is_integral_v<N>,
                  "integer::Gcd argument must be integers.");

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

    numericxx::Solution<M, N> ret(a1, x, y);
    return ret;
}
};  // namespace integer

#endif  // algorithms.h