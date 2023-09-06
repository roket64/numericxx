#ifndef CIPHER_H
#define CIPHER_H

#include <string>
#include <type_traits>
#include <vector>

#include "arithmetics.h"
#include "exceptions.h"

// Basic implementation of RSA encryption and decryption.
namespace numericxx {
namespace cipher {
template <class M, class N = i64>
std::vector<M> Encrypt(std::vector<M> a, const N &k, const N &p,
                       const N &q) noexcept {
    static_assert(std::is_integral_v<M> && std::is_integral_v<key_t>,
                  "integer::cipher::encrypt argument must be integer.");

    i64 prod = p * q;

    for (auto &i : a) {
        i = integer::powmod(i, k, prod);
    }

    return a;
}

template <class M>
std::vector<M> Decrypt(std::vector<M> a, const i64 &k, const i64 &m,
                       const i64 &key) {
    i64 phi = (key - 1) * (m / key - 1);

    const auto [g, u, v] = integer::gcd(k, phi);

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