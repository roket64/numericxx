#ifndef PRIMES_H
#define PRIMES_H

#include <vector>

#include "arithmetics.h"
#include "utilities.h"

namespace numericxx {
namespace details {
// Maximum value can be tested on fewer bases
constexpr i64 MILLER_TEST_THRESHOLD = 0x11baa74c5ll;
// Bases to test integer under 4,759,123,141
static constexpr i32 table32_[3]{2, 7, 61};
// Bases to test integer over or equal to 4,759,123,141
static constexpr i64 table64_[12]{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

/**
 * @brief Tests the given n is a prime number in a quite naive way.
 */
template <class T>
constexpr bool TrialDivision(const T &n) noexcept {
    static_assert(std::is_integral_v<T>,
                  "integer::TrialDivision argument must be integers.");

    if (n <= 1) return false;
    if (n == 2) return true;

    for (u64 d = 2; d * d <= n; ++d) {
        if (n % d == 0) return false;
    }

    return true;
}

/**
 * @brief Factorizes of the given n in a quite naive way.
 * @param n An integer should be factorized
 */
template <class T>
constexpr std::vector<T> TrialFactorization(T n) noexcept {
    static_assert(std::is_integral_v<T>,
                  "integer::TrialFactorization argument must be integers.");

    std::vector<T> ret;

    for (T i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            ret.push_back(i);
            n /= i;
        }
    }

    if (n != 1) ret.push_back(n);

    return ret;
}

/**
 * @brief Checks the given n satisfies a^d = 1 (mod n) or
 * a^((2^r) * d) = -1 (mod m) for some r(0 <= r < s).
 * @param n An integer should be tested
 * @param a An integer coprime to n
 * @param d An integer from n - 1 = 2^s * d
 * @param s An integer from n - 1 = 2^s * d
 */
constexpr bool MillerRabinTest(const u64 &n, const u64 &a, const i64 &d,
                               u16 s) noexcept {
    // calculate a^d mod n
    i64 x = numericxx::ModularExp(a, d, n);

    // case of a^d = 1 (mod n) or a^d = -1 (mod n)
    if (x == 1 || x == n - 1) return true;

    // finding r satisfies a^((2^r) * d) = -1 (mod n)
    for (u32 r = 1; r < s; ++r) {
        x = numericxx::ModularMultiply(x, x, n);
        if (x == n - 1) return true;
    }

    return false;
}

/**
 * @brief Tests a primality of the given integer less than 4,759,123,141.
 */
constexpr bool IsPrime32(const u64 &n) noexcept {
    const auto [d, s] = numericxx::BinaryExpansion(n - 1);

    for (const i32 &a : details::table32_) {
        if (n == a) return true;
        if (!details::MillerRabinTest(n, a, d, s)) return false;
    }

    return true;
}

/**
 * @brief Tests a primality of the given integer greater than 4,759,123,141.
 */
constexpr bool IsPrime64(const u64 &n) noexcept {
    const auto [d, s] = numericxx::BinaryExpansion(n - 1);

    for (const i64 &a : details::table64_) {
        if (n == a) return true;
        if (!details::MillerRabinTest(n, a, d, s)) return false;
    }

    return true;
}
}  // namespace details

/**
 * @brief Returns whether the given n is a prime number.
 * @param n An integer should be tested
 */
template <class T>
constexpr bool IsPrime(const T &n) noexcept {
    static_assert(std::is_integral_v<T>,
                  "integer::IsPrime argument must be an integer.");

    // all neagtive integers are not prime
    if (n <= 1) return false;
    if (n == 2) return true;

    return (n < detials::MILLER_TEST_THRESHOLD) ? details::IsPrime32(n)
                                                : details::IsPrime64(n);
}
}  // namespace numericxx

#endif  // primes.h