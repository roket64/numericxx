#ifndef CIPHER_H
#define CIPHER_H

#include <string>
#include <type_traits>
#include <vector>

#include "basic_arithmetics.h"
#include "exceptions.h"

// Basic implementation of RSA encryption and decryption.
namespace integer {
namespace cipher {
template <class M, class key_t = i64>
std::vector<M> encrypt(std::vector<M> a, const key_t &k, const key_t &p,
                       const key_t &q) noexcept {
    static_assert(std::is_integral_v<M> && std::is_integral_v<key_t>,
                  "integer::cipher::encrypt argument must be integer.");

    i64 prod = p * q;

    for (auto &i : a) {
        i = integer::powmod(i, k, prod);
    }

    return a;
}

template <class M>
std::vector<M> decrypt(std::vector<M> a, const long long &k, const long long &m,
                       const long long &key) {
    long long phi = (key - 1) * (m / key - 1);

    auto [g, u, v] = integer::gcd(k, phi);

    if (g != 1)
        throw exceptions::InvalidSolutionException(
            "There are more than one of possible solutions.");

    for (auto &i : a) {
        i = integer::powmod(i, u, m);
    }

    return a;
}
}  // namespace cipher
}  // namespace integer

#endif  // cipher.h