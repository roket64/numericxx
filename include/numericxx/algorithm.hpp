/**
 * @file algorithm.hpp
 * @author Jaeseok Lee
 * @brief Collection of algorithms in Number Theory
 * @version 0.1.0
 * @date 2025-03-14
 *
 * @copyright MIT License (c) 2025
 *
 */

#ifndef NUMERICXX_ALGORITHM_HPP_
#define NUMERICXX_ALGORITHM_HPP_

#include <cmath>
#include <tuple>
#include <type_traits>
#include <utility>

#include "types.hpp"

namespace numericxx {
/**
 * @brief Calculates absolute value of `x`.
 *
 * @tparam ReturnType An unsigned integer type. `u32` is used as default.
 * @tparam T An arithmetic type.
 * @param x An arbitrary arithmetical value.
 * @return Absolute value of `x`
 */
template <class ReturnType = u32, class T>
constexpr ReturnType abs(const T &x) noexcept {
  static_assert(
      sizeof(ReturnType) >= sizeof(T),
      "numericxx::abs() return type must be at least as large as the input.");
  static_assert(std::is_arithmetic_v<T>,
                "numericxx::abs() argument must be arithmetical.");

  return x < 0 ? -static_cast<ReturnType>(x) : static_cast<ReturnType>(x);
};

/**
 * @brief Calculates positive integer `d`, `s` such that `n = d * 2^s`
 *
 * @tparam T An integer type. `u32` is used as default.
 * @param n An integer should be decomposed.
 * @return `std::pair<T, u16>(d, s)` satisfies `n = d * 2^s`.
 */
template <class T = u32>
constexpr std::pair<T, u16> binary_expan(T n) noexcept {
  static_assert(std::is_integral_v<T>,
                "numericxx::binary_expan() argument must be integers.");
  if (n == 0)
    return std::make_pair(n, 0);

  u16 s = 0;

  while (~n & 1) {
    ++s;
    n >>= 1;
  }
  return std::make_pair(n, s);
}

template <class M, class N> class BezoutIdentity {
private:
  std::common_type_t<M, N> d;
  M coeff_a;
  N coeff_b;

public:
  BezoutIdentity() : d(0), coeff_a(0), coeff_b(0){};
  BezoutIdentity(std::common_type_t<M, N> _d, M _x, N _y)
      : d(_d), coeff_a(_x), coeff_b(_y){};

  std::common_type_t<M, N> get_gcd() const noexcept { return this->d; }
  M get_coeff_a() const noexcept { return this->coeff_a; }
  N get_coeff_b() const noexcept { return this->coeff_b; }
};

/**
 * @brief Calculates the greatest common divisor of the given integers.
 * @note The result may incorrect on signed values since it's using bitshift
 * operations
 * @tparam M An integer type.
 * @tparam N An integer type.
 * @param a An arbitrary integer value.
 * @param b An arbitrary integer value.
 * @return Greatest common divisor of the given integers.
 */
template <class M, class N>
constexpr std::common_type_t<M, N> gcd(M a, N b) noexcept {
  static_assert(std::is_integral_v<M> && std::is_integral_v<N>,
                "numericxx::gcd() argument must be integers.");
  if (a == 0 || b == 0)
    return 0;

  using common_t = std::common_type_t<M, N>;

  a = numericxx::abs<common_t>(a);
  b = numericxx::abs<common_t>(b);

  common_t d = 1;

  /* Remove powers of two from GCD */
  while ((~a & 1) && (~b & 1)) {
    a >>= 1;
    b >>= 1;
    d <<= 1;
  }

  /* At least one of them is now odd */
  while (a != 0) {
    while (~a & 1)
      a >>= 1;
    while (~b & 1)
      b >>= 1;

    /* Now both a and b are odd */
    if (a >= b)
      a = (a - b) >> 1;
    else
      b = (b - a) >> 1;
  }
  return d * b;
}

/**
 * @brief Calculates Bezout's Identity of the given integers.
 * @tparam M An integer type, `u32` is used as defualt.
 * @tparam N An integer type, `u32` is used as default.
 * @param a An arbitrary integer value.
 * @param b An arbitrary integer value.
 * @return Class `BezoutIdentity<M, N>(a, b)`.
 */
template <class M, class N>
constexpr numericxx::BezoutIdentity<M, N> ext_gcd(M a, N b) noexcept {
  static_assert(std::is_integral_v<M> && std::is_integral_v<N>,
                "numericxx::ext_gcd() argument must be integers.");

  using common_t = std::common_type_t<M, N>;

  a = numericxx::abs<common_t>(a);
  b = numericxx::abs<common_t>(b);

  M x = 1, x1 = 0;
  N y = 0, y1 = 1;

  common_t a1 = a, b1 = b;

  while (b1) {
    common_t q = a1 / b1;
    std::tie(x, x1) = std::make_pair(x1, x - q * x1);
    std::tie(y, y1) = std::make_pair(y1, y - q * y1);
    std::tie(a1, b1) = std::make_pair(b1, a1 - q * b1);
  }
  /* make x positive */
  x = x + b / a1;
  y = y - a / a1;

  numericxx::BezoutIdentity<M, N> ret(a1, x, y);
  return ret;
}
}; // namespace numericxx

#endif // algorithm.hpp