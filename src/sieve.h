#ifndef SIEVE_H
#define SIEVE_H

#include <vector>

#include "int_types.h"

namespace integer {
class Sieve {
   private:
    u64 size_;
    std::vector<u64> prime;
    std::vector<u64> spf;
    std::vector<u64> phi;
    std::vector<u64> exp;
    std::vector<u64> mob;

   public:
    Sieve(const u64 &sz) : size_(sz) {
        this->spf.assign(sz + 1, 0);
        this->phi.assign(sz + 1, 0);
        this->exp.assign(sz + 1, 0);
        this->mob.assign(sz + 1, 0);
        this->mob.size();

        this->phi[1] = 1;
        this->mob[1] = 1;

        for (u64 i = 2; i < sz + 1; ++i) {
            if (this->spf[i] == 0) {
                this->spf[i] = i;
                this->phi[i] = i - 1;
                this->exp[i] = 1;
                this->mob[i] = -1;
                this->prime.push_back(i);
            }

            for (auto &p : this->prime) {
                u64 pos = i * p;

                if (pos > sz) break;

                this->spf[pos] = p;
                this->phi[pos] = this->phi[i] * p;
                this->exp[pos] = this->exp[i] * p;
                this->mob[pos] = 0;

                if (i % p == 0) break;
            }
        }
    }

    constexpr std::vector<u64> &primes() noexcept { return this->prime; }

    constexpr u64 size() noexcept { return this->size_; }

    template <class T>
    constexpr bool is_prime(const T &k) noexcept {
        if (k == 1) return false;
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