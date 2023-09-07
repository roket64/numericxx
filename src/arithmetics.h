/**
 * @file arithmetics.h
 * @brief Components for performing integer arithmetics.
 */

#ifndef ARITHMETICS_H
#define ARITHMETICS_H

#include <cmath>
#include <tuple>
#include <type_traits>

#include "configs/config.h"
#include "exceptions.h"
#include "validator.h"

// Basic integer arithmetics, no support for real numbers or complexes.
namespace numericxx {
/**
 * @brief Calculates x * y modulo m.
 */
template <class M, class N, class ModuloType>
constexpr std::common_type_t<M, ModuloType> ModularMultiply(
    M x, N y, const ModuloType &m) {
    static_assert(std::is_integral_v<M> && std::is_integral_v<N>,
                  "numericxx::ModularMultiply argument must be integers.");
    static_assert(std::is_integral_v<ModuloType>,
                  "numericxx::ModularMultiply modulo value must be integers.");

    if (y < 0)
        throw exceptions::InvalidArgumentException(
            "exponent value must be a positive integer.");

    if (m == 0)
        throw exceptions::DividedByZeroException(
            "modulo value must be not zero.");

    std::common_type_t<M, ModuloType> ret = 0;

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
template <class M, class N, class ModuloType>
constexpr std::common_type_t<M, ModuloType> ModularExp(M x, N y,
                                                       const ModuloType &m) {
    static_assert(std::is_integral_v<M> && std::is_integral_v<N>,
                  "numericxx::ModularExp argument must be integers.");
    static_assert(std::is_integral_v<ModuloType>,
                  "numericxx::ModularExp modulo value must be integers.");

    if (y < 0)
        throw exceptions::InvalidArgumentException(
            "exponent value must be a positive integer.");

    if (m == 0)
        throw exceptions::DividedByZeroException(
            "modulo value must be not zero.");

    std::common_type_t<M, ModuloType> ret = 1;
    x %= m;

    while (y) {
        if (y & 1) ret = (i128)ret * x % m;
        x = (i128)x * x % m;
        y >>= (N)1;
    }

    return ret;
}
};  // namespace numericxx

#endif  // arithmetics.h