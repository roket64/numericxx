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
}  // namespace numericxx
#endif