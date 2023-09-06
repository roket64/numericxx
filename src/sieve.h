#ifndef SIEVE_H
#define SIEVE_H

#include <vector>

#include "configs/config.h"

namespace numericxx {
/**
 * @brief Basic implementation of Linear Sieve and some multiplication functions.
 * @param sz A size of the sieve.
 */
class Sieve {
   private:
    u64 size_;
    // list of primes
    std::vector<u64> prime_;
    // smallest prime factor
    std::vector<u64> spf_;
    // euler phi function
    std::vector<u64> phi_;
    // exponent
    std::vector<u64> exp_;
    // mobious function
    std::vector<u64> mob_;

   public:
    Sieve(const u64 &sz) : size_(sz) {
        this->spf_.assign(sz + 1, 0);
        this->phi_.assign(sz + 1, 0);
        this->exp_.assign(sz + 1, 0);
        this->mob_.assign(sz + 1, 0);
        this->mob_.assign(sz + 1, 0);

        this->phi_[1] = 1;
        this->mob_[1] = 1;

        for (u64 i = 2; i < sz + 1; ++i) {
            if (this->spf_[i] == 0) {
                this->spf_[i] = i;
                this->phi_[i] = i - 1;
                this->exp_[i] = 1;
                this->mob_[i] = -1;
                this->prime_.push_back(i);
            }

            for (auto &p : this->prime_) {
                u64 pos = i * p;

                if (pos > sz) break;

                this->spf_[pos] = p;
                this->phi_[pos] = this->phi_[i] * p;
                this->exp_[pos] = this->exp_[i] * p;
                this->mob_[pos] = 0;

                if (i % p == 0) break;
            }
        }
    }

    /**
     * @brief Returns list of prime numbers of the sieve.
     */
    constexpr std::vector<u64> &primes() noexcept { return this->prime_; }

    /**
     * @brief Returns size of the sieve.
     */
    constexpr u64 size() noexcept { return this->size_; }

    /**
     * @brief Returns whether an integer prime number.
     */
    template <class T>
    constexpr bool IsPrime(const T &k) noexcept {
        return (k <= 1 ? false : this->spf_[k] == k);
    }

    /**
     *  @brief Returns smallest prime factor of an integer.
     */
    template <class T>
    constexpr u64 SmallestPrimeFactor(const T &k) noexcept {
        return this->spf_[k];
    }

    /**
     * @brief Returns Euler Phi Funtion value of an integer.
     */
    template <class T>
    constexpr u64 Phi(const T &k) noexcept {
        return this->phi_[k];
    }

    template <class T>
    constexpr u64 Exponent(const T &k) noexcept {
        return this->exp_[k];
    }

    /**
     * @brief Returns Mobius Function value of an integer.
     */
    template <class T>
    constexpr u64 Mobius(const T &k) noexcept {
        return this->mob_[k];
    }

    /**
     * @brief Returns nth prime number of current sieve.
     */
    template <class T>
    constexpr u64 at(const T &n) noexcept {
        return this->prime_.at(n - 1);
    }
};  // class Sieve
}  // namespace integer

#endif  // sieve.h