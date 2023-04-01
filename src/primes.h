#ifndef PRIMES_H
#define PRIMES_H

#include <type_traits>

#include "arithmetics.h"

namespace integer {

namespace details {
static const int __table32[3]{2, 7, 61};
static const long long __table64[12]{2,  3,  5,  7,  11, 13,
                                     17, 19, 23, 29, 31, 37};

template <class T>
constexpr bool trial_division(const T &n) noexcept {
    for (T d = 0; d * d <= n; ++d) {
        if (n % d == 0) return false;
    }
    return true;
}

constexpr bool __check(const long long &n, const long long &a,
                       const long long &d, int s) noexcept {
    // calculate a^d mod n
    long long x = integer::powmod(a, d, n);

    // case of a^d = 1 (mod n) or a^d = -1 (mod n)
    if (x == 1 || x == n - 1) return true;

    for (int r = 1; r < s; ++r) {
        x = integer::mulmod(x, x, n);
        if (x == n - 1) return true;
    }

    return false;
}

template <class T>
// Calculate s, d such that n = 2^s * d to given n
constexpr std::pair<T, unsigned> __expansion(T n) noexcept {
    unsigned s = 0;

    while (~n & 1) {
        ++s;
        n >>= 1;
    }

    return std::make_pair(n, s);
}

template <class T>
constexpr std::vector<T> trial_factorization(T n) noexcept {
    std::vector<T> ret;

    for (T i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            ret.push_back(i);
            n /= i;
        }
    }
    if (n > 1) ret.push_back(n);

    return ret;
}
}  // namespace details

template <class T>
bool is_prime(const T &n);

template <>
constexpr bool is_prime(const int &n) {
    if (n <= 1) return false;
    if (n == 2) return true;

    auto [d, s] = details::__expansion(n - 1);

    for (auto &a : details::__table32) {
        if (n == a) return true;
        if (!details::__check(n, a, d, s)) return false;
    }

    return true;
}

template <>
constexpr bool is_prime(const long long &n) {
    if (n <= 1) return false;
    if (n == 2) return true;

    auto [d, s] = details::__expansion(n - 1);

    for (auto &a : details::__table64) {
        if (n == a) return true;
        if (!details::__check(n, a, d, s)) return false;
    }

    return true;
}
}  // namespace integer

#endif  // primes.h