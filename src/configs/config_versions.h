/**
 * @file config_versions.h
 * @brief Defines the version of the project and its components.
*/

#ifndef CONFIG_VERSIONS_H
#define CONFIG_VERSIONS_H

#define NUMERICXX_MAJOR 0
#define NUMERICXX_MINOR 1
#define NUMERICXX_PATCH 0

#if (defined(__GNUC__) || defined(__GNUG__)) && !defined(__clang__)
#define NUMERICXX_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

#if defined(__clang__) && defined(__apple_build_version__)
#define NUMERICXX_APPLE_CLANG_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(__clang__)
#define NUMERICXX_CLANG_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#endif

#if defined(_MSC_VER) && !defined(__clang__)
#define NUMERICXX_MSVC_VERSION (_MSC_VER)
#endif

#if defined(__INTEL_COMPILER) && !defined(__clang__)
#define NUMERICXX_INTEL_VERSION (__INTEL_COMPILER)
#endif

#endif // config_versions.h