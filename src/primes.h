#ifndef PRIMES_H
#define PRIMES_H

#include <type_traits>
#include <vector>

#include "basic_arithmetics.h"
#include "int_types.h"

namespace integer {
namespace details {
static constexpr i32 __table32[3]{
    2, 7, 61};  // bases to test integer under 4,759,123,141
static constexpr i64 __table64[12]{
    2,  3,  5,  7,  11, 13,
    17, 19, 23, 29, 31, 37};  // bases to test integer under 2^64

/**
 * @brief Test the given n is a prime number by trial divison.
 */
template <class T>
constexpr bool trial_division(const T &n) noexcept {
    for (T d = 0; d * d <= n; ++d) {
        if (n % d == 0) return false;
    }
    return true;
}

/**
 * @brief Factorization of the given n in a quite naive way.
 * @param n An integer should be factorized
 */
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

/**
 * @brief Calculate the s, d such that n = 2^s * d to given n.
 * @param n An integer should be decomposed to 2^s * d
 */
template <class T>
constexpr std::pair<T, unsigned> __expansion(T n) noexcept {
    unsigned s = 0;

    while (~n & 1) {
        ++s;
        n >>= static_cast<T>(1);
    }

    return std::make_pair(n, s);
}

/**
 * @brief Check the given n satisfies a^d = 1 (mod n) or a^d = -1 (mod n), or
 * some a^r = -1 (mod m).
 * @param n An integer should be tested
 * @param a An integer coprime to n
 * @param d An integer from n - 1 = 2^s * d
 * @param s An integer from n - 1 = 2^s * d
 */
constexpr bool __check(const i64 &n, const i64 &a, const i64 &d,
                      i32 s) noexcept {
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

/**
 * @brief Test a primality of the given n <= 4,759,123,141.
*/
constexpr bool _is_prime_32(const i64 &n) {
    auto [d, s] = details::__expansion(n - 1);

    for (const i32 &a : details::__table32) {
        if (n == a) return true;
        if (!details::__check(n, a, d, s)) return false;
    }

    return true;
}

/**
 * @brief Test a primality of the given n > 4,759,123,141.
*/
constexpr bool _is_prime_64(const i64 &n) {
    auto [d, s] = details::__expansion(n - 1);

    for (const i64 &a : details::__table64) {
        if (n == a) return true;
        if (!details::__check(n, a, d, s)) return false;
    }

    return true;
}
}  // namespace details

/**
 * @brief Test a primality of the given n.
 * @param n An integer should be tested
 */
template <class T>
constexpr bool is_prime(const T &n) noexcept {
    static_assert(std::is_integral_v<T>,
                  "integer::is_prime argument must be an integer.");

    if (n <= 1) return false;
    if (n == 2) return true;

    if (static_cast<u64>(n) >= 4759123141ULL) {
        return details::_is_prime_32(n);
    } else {
        return details::_is_prime_64(n);
    }
}
}  // namespace integer

#endif  // primes.h