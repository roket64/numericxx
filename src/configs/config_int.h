/**
 * @file config_int.h
 * @brief Defines integer types and their limits.
 */

#ifndef CONFIG_INT_H
#define CONFIG_INT_H

#include "config_versions.h"

namespace numericxx {

typedef short i16;
typedef unsigned short u16;

typedef int i32;
typedef unsigned int u32;

#if defined(NUMERICXX_MSVC_VERSION)

typedef signed _int64 i64;
typedef unsigned _int64 u64;

#else

typedef long long i64;
typedef unsigned long long u64;

#endif

#if (defined(__GNUC__) || defined(__GNUG__)) ||  \
    (defined(__NUMERICXX_MSC_VERSION) &&         \
     ((defined(_M_X64)) || defined(_M_IA64))) || \
    (defined(__INTEL_COMPILER) && defined(__x86_64__))

#if ((NUMERICXX_GCC_VERSION >= 30400) ||          \
     (NUMERICXX_LLVM_CLANG_VERSION >= 3000) ||    \
     (NUMERICXX_APPLE_CLANG_VERSION >= 40300)) && \
    (__SIZEOF_INT128__ >= 16)

typedef __int128_t i128;
typedef __uint128_t u128;

#endif
#endif

constexpr i16 I16_MAX = 32767;
constexpr i16 I16_MIN = -32768;
constexpr u16 U16_MAX = 65535;

constexpr i32 I32_MAX = 2147483647;
constexpr i32 I32_MIN = -2147483648;
constexpr u32 U32_MAX = 4294967295u;

constexpr i64 I64_MAX = 9223372036854775807ll;
constexpr i64 I64_MIN = -9223372036854775807ll - 1ll;
constexpr u64 U64_MAX = 0xffffffffffffffffull;

}  // namespace numericxx

#endif  // config_int.h