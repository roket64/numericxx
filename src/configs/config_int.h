/**
 * @file config_int.h
 * @brief Defines integer types and their limits.
 */

#ifndef CONFIG_INT_H
#define CONFIG_INT_H

#include "config_versions.h"

namespace integer {

typedef short i16;
typedef unsigned short u16;

typedef int i32;
typedef unsigned int u32;

typedef long long i64;
typedef long long u64;

constexpr i16 I16_MAX = 32767;
constexpr i16 I16_MIN = -32768;
constexpr u16 U16_MAX = 65535;

constexpr i32 I32_MAX = 2147483647;
constexpr i32 I32_MIN = -2147483648;
constexpr u32 U32_MAX = 4294967295;

constexpr i64 I64_MAX = 9223372036854775807;
constexpr i64 I64_MIN = -9223372036854775808;
constexpr u64 U64_MAX = 18446744073709551615;

}  // namespace integer

#endif  // config_int.h