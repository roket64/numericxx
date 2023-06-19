#ifndef INT_TYPES_H
#define INT_TYPES_H

typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;

constexpr i32 I32_MAX = 2'147'483'647;
constexpr i32 I32_MIN = -2'147'483'648;
constexpr u32 U32_MAX = 4'294'967'295;

constexpr i64 I64_MAX = 9'223'372'036'854'775'807;
constexpr i64 I64_MIN = -9'223'372'036'854'775'808;
constexpr u64 U64_MAX = 18'446'744'073'709'551'615;

#if defined(__GNUC__) || defined(__clang__)
typedef __int128_t i128;
typedef __uint128_t u128;
#endif

#endif  // int_types.h