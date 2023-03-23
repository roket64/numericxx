#ifndef ARITHMETICS_H
#define ARITHMETICS_H

#include <cstdlib>
#include <exception>
#include <tuple>
#include <type_traits>

// Components for performing integer arithmetics.
// Includes basic algorithms of number theory.

// Basic integer arithmetics, no support for real numbers or complexes.
namespace integer {

namespace excpetions {
class DivdiedByZeroException : public std::exception {
   public:
    DivdiedByZeroException(const char *msg) : message(msg){};
    const char *what() const noexcept override { return message; }

   private:
    const char *message;
};

class ValueOverflowException : public std::exception {
   public:
    ValueOverflowException(const char *msg) : message(msg){};
    const char *what() const noexcept override { return message; }

   private:
    const char *message;
};
}  // namespace excpetions

// Struct for gcd(a, b) and the coefficient of bezout's identity.
template <class M, class N>
struct solution {
    solution() : g(0), x(0), y(0) {}
    solution(std::common_type_t<M, N> _g, M _x, N _y) : g(_g), x(_x), y(_y) {}

    std::common_type_t<M, N> g;  // gcd of a, b
    M x;                         // coefficient of a
    N y;                         // coefficient of b
};

template <class M, class N>
// Calculate x * y mod m.
constexpr std::common_type_t<M, N> mulmod(M x, N y, const long long &m) {
    static_assert(std::is_integral_v<M>,
                  "integer::mulmod argument must be integers.");
    static_assert(std::is_integral_v<N>,
                  "integer::mulmod argument must be integers.");

    if (m == 0)
        throw excpetions::DivdiedByZeroException(
            "modulo value must be not zero.");

    std::common_type_t<M, N> ret = 0;

    while (y) {
        if (y & 1) ret = (__int128_t)(ret + x) % m;
        x = (__int128_t)2 * x % m;
        y >>= 1;
    }

    return ret;
}

template <class M, class N>
// Calculate x^y mod m.
constexpr std::common_type_t<M, N> powmod(M x, N y, const long long &m) {
    static_assert(std::is_integral_v<M>,
                  "integer::powmod argument must be integers.");
    static_assert(std::is_integral_v<N>,
                  "integer::powmod argument must be integers.");

    if (m == 0)
        throw excpetions::DivdiedByZeroException(
            "modulo value must be not zero.");

    std::common_type_t<M, N> ret = 1;
    x %= m;

    while (y) {
        if (y & 1) ret = (__int128_t)ret * x % m;
        x = (__int128_t)x * x % m;
        y >>= 1;
    }

    return ret;
}

// Calculate gcd of given a, b and the coefficient of bezout's identity.
template <class M, class N>
constexpr integer::solution<M, N> gcd(M a, N b) noexcept {
    static_assert(std::is_integral_v<M>,
                  "integer::gcd argument must be integers.");
    static_assert(std::is_integral_v<N>,
                  "integer::gcd argument must be integers.");

    // maybe this is a bad idea
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

    return integer::solution(a1, x, y);
}
}  // namespace integer

#endif  // arithmetics.h