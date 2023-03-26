#ifndef PRIMES_H
#define PRIMES_H

#include <type_traits>

#include "arithmetics.h"

namespace integer {

namespace details {
const static int __table32[3]{2, 7, 61};
const static long long __table64[12]{2,  3,  5,  7,  11, 13,
                                     17, 19, 23, 29, 31, 37};

template <class T>
bool __trial_div(const T &n) {
    for (T d = 0; d * d <= n; ++d) {
        if (n & d == 0) return false;
    }
    return true;
}

bool __check(const long long &n, const long long &a, const long long &d,
             int s) {
    long long x = integer::powmod(a, d, n);

    if (x == 1 || x == n - 1) return true;

    for (int r = 0; r < s - 1; ++r) {
        x = integer::mulmod(x, x, n);
        if (x == n - 1) return true;
    }

    return false;
}

template <class T>
// Calculate s, d such that n = 2^s * d to given n
std::pair<T, unsigned int> __decompose(T n) {
    unsigned int s = 0;

    while (~n & 1) {
        ++s;
        n >>= 1;
    }

    return std::make_pair(n, s);
}
}  // namespace details

template <class T>
bool is_prime(const T &n);

template <>
bool is_prime(const int &n) {
    if (n <= 1) return false;
    if (n == 2) return true;

    auto [d, s] = details::__decompose(n - 1);

    for (auto &a : details::__table32) {
        if (n == a) return true;
        if (!details::__check(n, a, d, s)) return false;
    }

    return true;
}

template <>
bool is_prime(const long long &n) {
    if (n <= 1) return false;
    if (n == 2) return true;

    auto [d, s] = details::__decompose(n - 1);

    for (auto &a : details::__table64) {
        if (n == a) return true;
        if (!details::__check(n, a, d, s)) return false;
    }

    return true;
}
}  // namespace integer

#endif  // primes.h