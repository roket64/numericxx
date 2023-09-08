#ifndef NUMERICXX_BIGINT_H
#define NUMERICXX_BIGINT_H

#include <limits>
#include <string>
#include <vector>

#include "configs/config.h"

namespace numericxx {
namespace details {

template <class T>
class _DivType {
   private:
   public:
    _DivType() : quot(0), rem(0){};
    _DivType(const T& quot, const T& rem) : quot(quot), rem(rem){
        static_assert(std::is_integral_v<T>,
                      "integer::_DivType argument must be integers.")
    };
    T quot;
    T rem;
};
}  // namespace details

class BigInteger {
    typedef details::_DivType<i64> _DivType;

   private:
    int sign;         // -1 for negative, 0 for zero, 1 for positive
    bool signedness;  // true for signed, false for unsigned
    std::vector<u16> digits;

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& n);
    friend std::ostream& operator>>(std::ostream& os, BigInteger& n);

   public:
    BigInteger();
    constexpr explicit BigInteger(const std::string& str);
    constexpr BigInteger(const char* str);
    constexpr explicit BigInteger(const i32& n);
    constexpr explicit BigInteger(const u32& n);
    constexpr explicit BigInteger(const i64& n);
    constexpr explicit BigInteger(const u64& n);
    constexpr explicit BigInteger(const BigInteger& n);

    // arithmetic operators
    BigInteger operator+(const BigInteger& other) const;
    BigInteger operator-(const BigInteger& other) const;
    BigInteger operator*(const BigInteger& other) const;
    BigInteger operator/(const BigInteger& other) const;
    BigInteger operator%(const BigInteger& other) const;

    // relational operators
    bool operator<(const BigInteger& other) const;
    bool operator>(const BigInteger& other) const;
    bool operator<=(const BigInteger& other) const;
    bool operator>=(const BigInteger& other) const;
    bool operator==(const BigInteger& other) const;
    bool operator!=(const BigInteger& other) const;

    // assignment operators
    BigInteger& operator=(const std::string& str);
    BigInteger& operator=(const char* str);
    BigInteger& operator=(const i32& n);
    BigInteger& operator=(const u32& n);
    BigInteger& operator=(const i64& n);
    BigInteger& operator=(const u64& n);
    BigInteger& operator=(const BigInteger& n);

    // operational assignments
    const BigInteger& operator+=(const BigInteger& other);
    const BigInteger& operator-=(const BigInteger& other);
    const BigInteger& operator*=(const BigInteger& other);
    const BigInteger& operator/=(const BigInteger& other);
    const BigInteger& operator%=(const BigInteger& other);

    // increment, decrement operators
    const BigInteger& operator++();
    const BigInteger& operator--();
    BigInteger operator++(int);
    BigInteger operator--(int);
};
}  // namespace numericxx

namespace std {
template <>
class numeric_limits<numericxx::BigInteger> {
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed = true;
    static constexpr bool is_integer = true;
    static constexpr bool is_exact = true;
    static constexpr bool has_infinity = false;
    static constexpr bool has_quiet_NaN = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr bool has_denorm = false;
    static constexpr bool has_denorm_loss = false;
    static constexpr std::float_round_style round_style =
        std::float_round_style::round_toward_zero;
    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = true;
    static constexpr int digits = 0;
    static constexpr int digits10 = 0;
    static constexpr int max_digits10 = 0;
    static constexpr int radix = 0;
    static constexpr int min_exponent = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int max_exponent = 0;
    static constexpr int max_exponent10 = 0;
};
}  // namespace std
#endif  // bigint.h