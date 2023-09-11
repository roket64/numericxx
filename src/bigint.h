#ifndef NUMERICXX_BIGINT_H
#define NUMERICXX_BIGINT_H

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>
#include <vector>

#include "configs/config.h"
#include "exceptions.h"

namespace numericxx {
namespace details {

template <class T>
class _DivType {
   private:
   public:
    _DivType() : quot_(0), rem_(0){};
    _DivType(const T& quot, const T& rem) : quot_(quot), rem_(rem) {
        static_assert(std::is_integral_v<T>,
                      "integer::_DivType argument must be integers.");
    }
    T quot_;
    T rem_;
};

typedef details::_DivType<i32> DivType;
typedef details::_DivType<i64> DivTypell;

static DivType _div(const i32& a, const i32& b) {
    if (b == 0)
        throw exceptions::DividedByZeroException(
            "numericxx::exceptions::_div denumerator must be not zero.");

    DivType ret;
    ret.quot_ = a / b;
    ret.rem_ = a % b;
    return ret;
}

static DivTypell _divll(const i64& a, const i64& b) {
    if (b == 0)
        throw exceptions::DividedByZeroException(
            "numericxx::exceptions::_div denumerator must be not zero.");

    DivTypell ret;
    ret.quot_ = a / b;
    ret.rem_ = a % b;
    return ret;
}

}  // namespace details

class BigInteger {
    friend std::istream& operator>>(std::istream& is, BigInteger& n) {
        std::string str;
        is >> str;
        n.ConvertFromString(str);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& n) {
        if (n.sign_ == 0) {
            os << 0;
            return os;
        }

        if (n.sign_ == -1) os << '-';

        bool begin = true;

        for (i32 i = static_cast<i32>(n.value_.size()) - 1; i >= 0; --i) {
            if (begin) {
                os << n.value_[i];
                begin = false;
            } else {
                os << std::setw(BigInteger::BASE_DIGITS) << std::setfill('0')
                   << n.value_[i];
            }
        }

        return os;
    }

   private:
    i16 sign_;         // -1 for negative, 0 for zero, 1 for positive
    bool signedness_;  // true for signed, false for unsigned
    std::vector<i32> value_;

    static constexpr i32 BASE = 1000000000;
    static constexpr i32 BASE_DIGITS = 9;
    static constexpr i32 BASE_UPPER_BOUND = 999999999;

   public:
    explicit BigInteger() : sign_(0), signedness_(true) {
        value_.clear();
        value_.push_back(0);
    }

    explicit BigInteger(i32 n) : sign_(n != 0 ? n > 0 : 0), signedness_(true) {
        if (sign_ < 0) n = -n;

        while (n > 0) {
            details::DivType div = details::_div(n, BASE);
            value_.push_back(static_cast<i32>(div.rem_));
            n = div.quot_;
        }
    }

    explicit BigInteger(u32 n) : sign_(n > 0 ? 1 : 0), signedness_(false) {
        while (n > 0) {
            details::DivType div = details::_div(n, BASE);
            value_.push_back(static_cast<i32>(div.rem_));
            n = div.quot_;
        }
    }

    explicit BigInteger(i64 n) : sign_(n != 0 ? n > 0 : 0), signedness_(true) {
        if (sign_ < 0) n = -n;

        while (n > 0) {
            details::DivTypell div = details::_divll(n, BASE);
            value_.push_back(static_cast<i32>(div.rem_));
            n = div.quot_;
        }
    }

    explicit BigInteger(u64 n) : sign_(n > 0 ? 1 : 0), signedness_(false) {
        while (n > 0) {
            details::DivTypell div = details::_divll(n, BASE);
            value_.push_back(static_cast<i32>(div.rem_));
            n = div.quot_;
        }
    }

    explicit BigInteger(const BigInteger& n)
        : sign_(n.sign_), signedness_(n.signedness_), value_(n.value_){};

    explicit BigInteger(const std::string& str) { ConvertFromString(str); }

    explicit BigInteger(const char* c) { ConvertFromString(c); }

    BigInteger operator-() const;

    // arithmetic operators
    /*
    BigInteger operator+(const BigInteger& other) const {
        BigInteger ret;

        ret.value_.resize(std::max(this->value_.size(), other.value_.size()));

        for (size_t i = 0; i < this->value_.size() || i < other.value_.size();
             ++i) {
            if (i < this->value_.size())
                ret.value_[i] +=
                    this->sign_ < 0 ? -this->value_[i] : this->value_[i];

            if (i < other.value_.size())
                ret.value_[i] +=
                    other.sign_ < 0 ? -other.value_[i] : other.value_[i];
        }

        ret.ValidateValue();
        // TODO: why this doesn't work?
        // return ret;
    }
    /**/

    /*
    BigInteger operator-(const BigInteger& other) const {
        BigInteger ret;

        ret.value_.resize(std::max(this->value_.size(), other.value_.size()));

        for (size_t i = 0; i < this->value_.size() || i < other.value_.size();
             ++i) {
            if (i < this->value_.size())
                ret.value_[i] -=
                    this->sign_ < 0 ? -this->value_[i] : this->value_[i];

            if (i < other.value_.size())
                ret.value_[i] -=
                    other.sign_ < 0 ? -other.value_[i] : other.value_[i];
        }

        ret.ValidateValue();

        // TODO: why this doesn't work?
        // return ret;
    }
    /**/

    BigInteger operator*(const BigInteger& other) const;
    BigInteger operator/(const BigInteger& other) const;
    BigInteger operator%(const BigInteger& other) const;

    // relational operators
    bool operator==(const BigInteger& other) const {
        if (this->sign_ != other.sign_ ||
            this->value_.size() != other.value_.size())
            return false;
    
        for (size_t i = 0; i < this->value_.size(); ++i)
            if (this->value_[i] != other.value_[i]) return false;

        return true;
    }

    bool operator!=(const BigInteger& other) const { return !(*this == other); }

    bool operator<(const BigInteger& other) const {
        if (this->sign_ < other.sign_)
            return true;
        else if (this->sign_ > other.sign_)
            return false;

        if (this->value_.size() < other.value_.size())
            return true;
        else if (this->value_.size() > other.value_.size())
            return false;

        for (i32 i = static_cast<i32>(this->value_.size()) - 1; i >= 0; --i) {
            if (this->value_[i] < other.value_[i])
                return true;
            else if (this->value_[i] > other.value_[i])
                return false;
        }

        return false;
    }

    bool operator>(const BigInteger& other) const {
        if (this->sign_ > other.sign_)
            return true;
        else if (this->sign_ < other.sign_)
            return false;

        if (this->value_.size() > other.value_.size())
            return true;
        else if (this->value_.size() < other.value_.size())
            return false;

        for (i32 i = static_cast<i32>(this->value_.size()) - 1; i >= 0; --i) {
            if (this->value_[i] > other.value_[i])
                return true;
            else if (this->value_[i] < other.value_[i])
                return false;
        }

        return false;
    }

    bool operator<=(const BigInteger& other) const { return !(*this > other); }

    bool operator>=(const BigInteger& other) const { return !(*this < other); }

    // assignment operators
    BigInteger& operator=(const std::string& str) {
        ConvertFromString(str);
        return *this;
    }

    BigInteger& operator=(const char* str) {
        ConvertFromString(str);
        return *this;
    }

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

    /**
     * @brief Adjust elements of the value vector to be in the range of the BASE
     */
    void ShrinkToBase() {
        for (size_t i = 0; i < value_.size(); ++i) {
            if (value_[i] >= BASE || value_[i] <= -BASE) {
                details::DivType div = details::_div(value_[i], BASE);
                value_[i] = div.rem_;

                // end of the vector
                if (i + 1 == value_.size()) {
                    value_.push_back(div.quot_);
                } else {
                    value_[i + 1] += div.quot_;
                }
            }
        }
    }

    // TODO: implement this later 2
    void EqualizeSigns();

    /**
     * @brief Removes leading zeros from the value.
     */
    void RemoveLeadingZeros() {
        for (i32 i = static_cast<i32>(value_.size()) - 1; i > 0; --i) {
            if (value_[i] != 0) {
                return;
            } else {
                value_.erase(value_.begin() + i);
            }
        }
    }

    void ValidateValue(bool chk_leading_zeros_only = false,
                       bool has_valid_sign = false) {
        if (!chk_leading_zeros_only) {
            ShrinkToBase();
            EqualizeSigns();
        }

        RemoveLeadingZeros();
    }

    /**
     * @brief Convert std::string to BigInteger
     */
    void ConvertFromString(const std::string& str) {
        sign_ = 1;
        signedness_ = true;

        value_.clear();
        value_.reserve(str.size() / BASE_DIGITS + 1);
        i32 idx = static_cast<i32>(str.size()) - BASE_DIGITS;

        // appending digits in groups of BASE_DIGITS
        for (; idx >= 0; idx -= BASE_DIGITS) {
#if __cplusplus >= 201103L  // supports std::stoi()
            std::string substr_ = str.substr(idx, BASE_DIGITS);
            const i32 val_ = std::stoi(substr_);
            value_.push_back(val_);
#else
            const char* substr_ = str.substr(idx, BASE_DIGITS).c_str();
            const i32 val_ = std::atoi(substr_);
            value_.push_back(val_);
#endif
        }

        // appending remaining digits
        if (idx > -BASE_DIGITS) {
#if __cplusplus >= 201103L  // supports std::stoi()
            std::string substr_ = str.substr(0, idx + BASE_DIGITS);
            if (substr_.size() == 1 && substr_[0] == '-') {
                sign_ = -1;
            } else {
                const i32 val_ = std::stoi(substr_);
                value_.push_back(val_);
            }
#else
            const char* substr_ = str.substr(0, idx + BASE_DIGITS).c_str();
            if (substr_.size() == 1 && substr_[0] == '-') {
                sign_ = -1;
            } else {
                const i32 val_ = std::atoi(substr_).c_str();
                value_.push_back(val_);
            }
#endif
        }

        if (value_.back() < 0) {
            sign_ = -1;
            value_.back() = -value_.back();
        }

        ValidateValue(true);
    }
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