#ifndef UTILITIES_H
#define UTILITIES_H

#include <type_traits>

namespace numericxx {
template <class ReturnType, class T>
constexpr ReturnType Abs(const T &x) noexcept {
    static_assert(
        sizeof(ReturnType) >= sizeof(T),
        "numericxx::Abs return type must be at least as large as the input.");
    static_assert(std::is_arithmetic_v<T>,
                  "numericxx::Abs argument must be arithmetical.");

    return x < 0 ? -static_cast<ReturnType>(x) : static_cast<ReturnType>(x);
};

/**
 * @brief Calculates integer s, d such that n = 2^s * d to given n.
 * @param n An integer should be decomposed to 2^s * d
 */
template <class T>
constexpr std::pair<T, u16> BinaryExpansion(T n) noexcept {
    static_assert(std::is_integral_v<T>,
                  "numericxx::BinaryExpansion argument must be integers.");

    // the loop under will permanently continue without this line
    if (n == 0) return std::make_pair(n, 0);

    u16 s = 0;

    // divide n by 2 until n is odd
    while (~n & 1U) {
        ++s;
        // TODO: I don't think static cast is needed here
        // n >>= static_cast<T>(1);
        n >>= 1;
    }

    return std::make_pair(n, s);
}
}  // namespace numericxx
#endif