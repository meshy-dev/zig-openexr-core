// ImathConfig.h for zig-openexr
// Auto-generated for static library build with F16C support

#ifndef INCLUDED_IMATH_CONFIG_H
#define INCLUDED_IMATH_CONFIG_H 1

#pragma once

//
// Version information - Imath 3.2.1
//
#define IMATH_VERSION_MAJOR 3
#define IMATH_VERSION_MINOR 2
#define IMATH_VERSION_PATCH 1

#define IMATH_VERSION_STRING "3.2.1"
#define IMATH_PACKAGE_STRING "Imath"
#define IMATH_VERSION_RELEASE_TYPE ""

#define IMATH_VERSION_HEX \
    ((uint32_t(IMATH_VERSION_MAJOR) << 24) | \
     (uint32_t(IMATH_VERSION_MINOR) << 16) | \
     (uint32_t(IMATH_VERSION_PATCH) << 8))

#define IMATH_LIB_VERSION_STRING "30.2.1"

//
// Namespace configuration (simple defaults)
//
#define IMATH_INTERNAL_NAMESPACE_CUSTOM 0
#define IMATH_INTERNAL_NAMESPACE Imath_3_2
#define IMATH_NAMESPACE_CUSTOM 0
#define IMATH_NAMESPACE Imath

//
// Do NOT use lookup table - prefer F16C hardware or bit-shift algorithm
// This avoids needing to link half.cpp which has the 128KB lookup table
//
// #define IMATH_HALF_USE_LOOKUP_TABLE

//
// Enable noexcept
//
#define IMATH_USE_NOEXCEPT 1
#define IMATH_NOEXCEPT noexcept

//
// Enable foreign vector interop
//
#ifndef IMATH_FOREIGN_VECTOR_INTEROP
#    if defined(__GNUC__) && __GNUC__ == 4 && !defined(__clang__)
#        define IMATH_FOREIGN_VECTOR_INTEROP 0
#    else
#        define IMATH_FOREIGN_VECTOR_INTEROP 1
#    endif
#endif

//
// CUDA/HIP device decorator (not used in our build)
//
#if defined(__CUDACC__) || defined(__HIP__)
#    define IMATH_HOSTDEVICE __host__ __device__
#else
#    define IMATH_HOSTDEVICE
#endif

//
// Branch prediction hints
//
#if defined(__GNUC__) || defined(__clang__) || defined(__INTEL_COMPILER)
#    ifdef __cplusplus
#        define IMATH_LIKELY(x) (__builtin_expect(static_cast<bool>(x), true))
#        define IMATH_UNLIKELY(x) (__builtin_expect(static_cast<bool>(x), false))
#    else
#        define IMATH_LIKELY(x) (__builtin_expect((x), 1))
#        define IMATH_UNLIKELY(x) (__builtin_expect((x), 0))
#    endif
#else
#    define IMATH_LIKELY(x) (x)
#    define IMATH_UNLIKELY(x) (x)
#endif

//
// __has_attribute support
//
#ifndef __has_attribute
#    define __has_attribute(x) 0
#endif

//
// Deprecation macro
//
#if defined(_MSC_VER)
#    define IMATH_DEPRECATED(msg) __declspec(deprecated(msg))
#elif defined(__cplusplus) && __cplusplus >= 201402L
#    define IMATH_DEPRECATED(msg) [[deprecated(msg)]]
#elif defined(__GNUC__) || defined(__clang__)
#    define IMATH_DEPRECATED(msg) __attribute__((deprecated(msg)))
#else
#    define IMATH_DEPRECATED(msg)
#endif

//
// Symbol visibility (static library - no DLL export)
//
// #define IMATH_ENABLE_API_VISIBILITY

#endif // INCLUDED_IMATH_CONFIG_H
