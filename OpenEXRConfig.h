// Minimal OpenEXRConfig.h for zig-openexr
// Auto-generated for static library build

#ifndef INCLUDED_OPENEXR_CONFIG_H
#define INCLUDED_OPENEXR_CONFIG_H 1

#pragma once

#define OPENEXR_VERSION_MAJOR 3
#define OPENEXR_VERSION_MINOR 4
#define OPENEXR_VERSION_PATCH 4

#define OPENEXR_VERSION_STRING "3.4.4"
#define OPENEXR_PACKAGE_STRING "OpenEXR"
#define OPENEXR_VERSION_RELEASE_TYPE ""
#define OPENEXR_LIB_VERSION_STRING "31.4.4"

#define OPENEXR_VERSION_HEX \
    (((OPENEXR_VERSION_MAJOR) << 24) | \
     ((OPENEXR_VERSION_MINOR) << 16) | \
     ((OPENEXR_VERSION_PATCH) << 8))

// Imath version - use 3.0 to trigger fallback half-float code in OpenEXRCore
#define OPENEXR_IMATH_VERSION_MAJOR 3
#define OPENEXR_IMATH_VERSION_MINOR 0
#define OPENEXR_IMATH_VERSION_PATCH 0

// OpenJPH disabled
#define OPENEXR_OPENJPH_VERSION_MAJOR 0
#define OPENEXR_OPENJPH_VERSION_MINOR 0
#define OPENEXR_OPENJPH_VERSION_PATCH 0

// C++ namespace config (not used in Core C API)
#define OPENEXR_IMF_INTERNAL_NAMESPACE_CUSTOM 0
#define OPENEXR_IMF_INTERNAL_NAMESPACE Imf
#define OPENEXR_IMF_NAMESPACE_CUSTOM 0
#define OPENEXR_IMF_NAMESPACE Imf

// Static library - no DLL export/import
#define OPENEXR_EXPORT
#define OPENEXR_HIDDEN
#define OPENEXR_EXPORT_TYPE
#define OPENEXR_EXPORT_EXTERN_TEMPLATE
#define OPENEXR_EXPORT_ENUM
#define OPENEXR_EXPORT_TEMPLATE_TYPE
#define OPENEXR_EXPORT_TEMPLATE_INSTANCE

#if defined(__cplusplus) && (__cplusplus >= 201402L)
#    define OPENEXR_DEPRECATED(msg) [[deprecated(msg)]]
#elif defined(__GNUC__) || defined(__clang__)
#    define OPENEXR_DEPRECATED(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
#    define OPENEXR_DEPRECATED(msg) __declspec(deprecated(msg))
#else
#    define OPENEXR_DEPRECATED(msg)
#endif

#endif // INCLUDED_OPENEXR_CONFIG_H
