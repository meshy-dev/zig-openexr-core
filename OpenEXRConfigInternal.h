// OpenEXRConfigInternal.h for zig-openexr
// Auto-generated for static library build

#ifndef INCLUDED_OPENEXR_INTERNAL_CONFIG_H
#define INCLUDED_OPENEXR_INTERNAL_CONFIG_H 1

#pragma once

// Use external libdeflate (we build it separately)
// #define OPENEXR_USE_INTERNAL_DEFLATE 1

// Linux proc filesystem
#if defined(__linux__)
#define OPENEXR_IMF_HAVE_LINUX_PROCFS 1
#endif

// Darwin (macOS)
#if defined(__APPLE__)
#define OPENEXR_IMF_HAVE_DARWIN 1
#endif

// Complete iomanip support (C++ only, not needed for Core C API)
#define OPENEXR_IMF_HAVE_COMPLETE_IOMANIP 1

// sysconf for CPU count
#if defined(__linux__) || defined(__APPLE__) || defined(__unix__)
#define OPENEXR_IMF_HAVE_SYSCONF_NPROCESSORS_ONLN 1
#endif

// GCC inline asm with AVX (x86_64)
#if defined(__GNUC__) && defined(__x86_64__) && defined(__AVX__)
#define OPENEXR_IMF_HAVE_GCC_INLINE_ASM_AVX 1
#endif

// ARM NEON vld1q_f32_x2 availability - only define on ARM if intrinsic is missing
// Do NOT define on x86/x64 as the workaround code uses ARM NEON types
#if defined(__aarch64__) && !defined(vld1q_f32_x2)
#define OPENEXR_MISSING_ARM_VLD1 1
#endif

#endif // INCLUDED_OPENEXR_INTERNAL_CONFIG_H
