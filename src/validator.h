#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <type_traits>

#include "configs/config.h"

namespace numericxx {
template <class T>
constexpr bool IsPositive(const T &n) {
    static_assert(std::is_integral_v<T>,
                  "numericxx::IsPositive argument must be integers.");

    return n > 0;
}

template <class T>
constexpr bool IsNegative(const T &n) {
    static_assert(std::is_integral_v<T>,
                  "numericxx::IsNegative argument must be integers.");

    return n < 0;
}

template <class T>
constexpr bool IsZero(const T &n) {
    static_assert(std::is_integral_v<T>,
                  "numericxx::IsZero argument must be integers.");

    return n == 0;
}

};  // namespace numericxx

#endif  // validator.h