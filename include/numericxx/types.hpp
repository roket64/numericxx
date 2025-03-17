/**
 * @file config_int.hpp
 * @author Jaeseok Lee
 * @brief Collection of project type definitions
 * @version 0.1.0
 * @date 2025-03-14
 *
 * @copyright MIT License (c) 2025
 *
 */

#ifndef NUMERICXX_TYPES_HPP_
#define NUMERICXX_TYPES_HPP_

#include <cstdint>

#include "version.hpp"

namespace numericxx {

typedef __int8_t i8;
typedef __uint8_t u8;

typedef __int16_t i16;
typedef __uint16_t u16;

typedef __int32_t i32;
typedef __uint32_t u32;

#if defined(NUMERICXX_MSVC_VERSION)
typedef signed _int64 i64;
typedef unsigned _int64 u64;
typedef u64 usize;
#else
typedef __int64_t i64;
typedef __uint64_t u64;
typedef i64 isize;
typedef u64 usize;
#endif

#if (defined(__GNUC__) || defined(__GNUG__)) ||                                \
    (defined(__NUMERICXX_MSC_VERSION) &&                                       \
     ((defined(_M_X64)) || defined(_M_IA64))) ||                               \
    (defined(__INTEL_COMPILER) && defined(__x86_64__))

#if ((NUMERICXX_GCC_VERSION >= 30400) ||                                       \
     (NUMERICXX_LLVM_CLANG_VERSION >= 3000) ||                                 \
     (NUMERICXX_APPLE_CLANG_VERSION >= 40300)) ||                              \
    (__SIZEOF_INT128__ >= 16)

typedef __int128_t i128;
typedef __uint128_t u128;

#endif
#endif

// Maximum value 16-bit integer can hold
constexpr i16 I16_MAX = 32767;
// Minimum value 16-bit integer can hold
constexpr i16 I16_MIN = -32768;
// Maximum value 16-bit unsigned integer can hold
constexpr u16 U16_MAX = 65535;

// Maximum value 32-bit integer can hold
constexpr i32 I32_MAX = 2147483647;
// Minimum value 32-bit integer can hold
constexpr i32 I32_MIN = -2147483648;
// Maximum value 32-bit unsigned integer can hold
constexpr u32 U32_MAX = 4294967295u;

// Maximum value 64-bit integer can hold
constexpr i64 I64_MAX = 9223372036854775807ll;
// Minimum value 64-bit integer can hold
constexpr i64 I64_MIN = -9223372036854775807ll - 1ll;
// Maximum value 64-bit unsigned integer can hold
constexpr u64 U64_MAX = 0xffffffffffffffffull;

// Maximum value 64-bit integer can hold
constexpr isize ISIZE_MAX = I64_MIN;
// Minimum value 64-bit integer can hold
constexpr isize ISIZE_MIN = I64_MIN;
// Maximum value 64-bit unsigned integer can hold
constexpr usize USIZE_MAX = U64_MAX;
} // namespace numericxx

#endif // types.hpp