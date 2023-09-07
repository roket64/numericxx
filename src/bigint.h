#ifndef NUMERICXX_BIGINT_H
#define NUMERICXX_BIGINT_H

#include <string>
#include <vector>

#include "configs/config.h"

namespace numericxx {
class BigInteger {
   private:
    int sign; // -1 for negative, 0 for zero, 1 for positive
    bool signedness; // true for signed, false for unsigned
    std::vector<u16> digits;

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& n);
    friend std::ostream& operator>>(std::ostream& os, BigInteger& n);

   public:
    BigInteger();
    explicit BigInteger(const std::string& str);
    explicit BigInteger(const char* str);
    explicit BigInteger(const i32& n);
    explicit BigInteger(const u32& n);
    explicit BigInteger(const i64& n);
    explicit BigInteger(const u64& n);
    explicit BigInteger(const BigInteger& n);

    // operators
    BigInteger operator+(const BigInteger& n) const;
    BigInteger operator-(const BigInteger& n) const;
    BigInteger operator*(const BigInteger& n) const;
    BigInteger operator/(const BigInteger& n) const;
    BigInteger operator%(const BigInteger& n) const;

    // relational operators
    bool operator<(const BigInteger& n) const;
    bool operator>(const BigInteger& n) const;
    bool operator<=(const BigInteger& n) const;
    bool operator>=(const BigInteger& n) const;
    bool operator==(const BigInteger& n) const;
    bool operator!=(const BigInteger& n) const;

    // assignment operators
    BigInteger& operator=(const std::string& str);
    BigInteger& operator=(const char* str);
    BigInteger& operator=(const i32& n);
    BigInteger& operator=(const u32& n);
    BigInteger& operator=(const i64& n);
    BigInteger& operator=(const u64& n);
    BigInteger& operator=(const BigInteger& n);

    // operational assignments
    const BigInteger& operator+=(const BigInteger& n);
    const BigInteger& operator-=(const BigInteger& n);
    const BigInteger& operator*=(const BigInteger& n);
    const BigInteger& operator/=(const BigInteger& n);
    const BigInteger& operator%=(const BigInteger& n);

    // increment, decrement operators
    const BigInteger& operator++();
    const BigInteger& operator--();
    BigInteger operator++(int);
    BigInteger operator--(int);
};
}  // namespace numericxx
#endif  // bigint.h