#ifndef SIEVE_H
#define SIEVE_H

#include <vector>

#include "int_types.h"

namespace integer {
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
        this->mob_.size();

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

    constexpr std::vector<u64> &primes() noexcept { return this->prime_; }

    constexpr u64 size() noexcept { return this->size_; }

    template <class T>
    constexpr bool is_prime(const T &k) noexcept {
        if (k <= 1) return false;
        return this->spf[k] == k;
    }

    template <class T>
    constexpr u64 smallest_p_factor(const T &k) noexcept {
        return this->spf[k];
    }

    template <class T>
    constexpr u64 euler_phi(const T &k) noexcept {
        return this->phi[k];
    }

    template <class T>
    constexpr u64 exponent(const T &k) noexcept {
        return this->exp[k];
    }

    template <class T>
    constexpr u64 mobius(const T &k) noexcept {
        return this->mob[k];
    }
};  // class Sieve
}  // namespace integer

#endif  // sieve.h