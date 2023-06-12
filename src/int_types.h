#ifndef INT_TYPES_H
#define INT_TYPES_H

typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;

#if defined(__GNUC__) || defined(__clang__)
typedef __int128_t i128;
typedef __uint128_t u128;
#endif

#endif  // int_types.h