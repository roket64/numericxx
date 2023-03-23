#ifndef PRIMES_H
#define PRIMES_H

#include <type_traits>

#include "arithmetics.h"

namespace details {
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
}  // namespace details

template <class T>
bool is_prime(const T &n) {}

template <>
bool is_prime(const int &n) {
    if (n <= 1) return false;
    if (n == 2) return true;

    int s = 0;
    int d = n - 1;
    while (~d & 1) {
        ++s;
        d >>= 1;
    }

    for (auto &a : {2, 7, 61}) {
        if (n == a) return true;
        if (!details::__check(n, a, d, s)) return false;
    }

    return true;
}

template <>
bool is_prime(const long long &n) {
    if (n <= 1) return false;
    if (n == 2) return true;

    int s = 0;
    long long d = n - 1;
    while (~d & 1LL) {
        ++s;
        d >>= 1LL;
    }

    for (auto &a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        if (!details::__check(n, a, d, s)) return false;
    }

    return true;
}

#endif  // primes.h