#pragma once

// OS detection
#if defined(_WIN32) || defined(_WIN64)
#   define _OS_WINDOWS
#elif defined(__linux__)
#   define _OS_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
#   define _OS_MACOS
#endif

// compiler detection
#if defined(_MSC_VER)
#   define _COMPILER_MSVC
#elif defined(__GNUC__)
#   define _COMPILER_GCC
#elif defined(__clang__)
#   define _COMPILER_CLANG
#else
#   error "Unsupported compiler"
#endif

#ifdef _OS_WINDOWS
#   define _MCS_EXPORT __declspec(dllexport)
#   define _MCS_IMPORT __declspec(dllimport)
#else
#   if defined(_COMPILER_GCC) || defined(_COMPILER_CLANG)
#       define _MCS_EXPORT __attribute__((visibility("default")))
#       define _MCS_IMPORT
#   else
#       define _MCS_EXPORT
#       define _MCS_IMPORT
#   endif
#endif

#ifdef _BUILD_MCS_LIBRARIES
#   define _MCS_LIB_API _MCS_EXPORT
#else
#   define _MCS_LIB_API _MCS_IMPORT
#endif

