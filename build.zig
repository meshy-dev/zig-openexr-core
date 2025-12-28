const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const openexr_dep = b.dependency("openexr", .{});
    const deflate_dep = b.dependency("libdeflate", .{});
    const imath_dep = b.dependency("imath", .{});

    // Build libdeflate first
    const deflate_mod = b.createModule(.{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });
    deflate_mod.addIncludePath(deflate_dep.path(""));
    deflate_mod.addCSourceFiles(.{
        .root = deflate_dep.path(""),
        .files = deflate_srcs,
        .flags = &.{ "-fPIC", "-Wall", "-O3" },
    });
    const libdeflate = b.addLibrary(.{
        .name = "deflate",
        .linkage = .static,
        .root_module = deflate_mod,
    });

    // Build OpenEXRCore
    const exr_mod = b.createModule(.{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });

    // Add include paths
    exr_mod.addIncludePath(openexr_dep.path("src/lib/OpenEXRCore"));
    exr_mod.addIncludePath(deflate_dep.path("")); // for libdeflate.h
    exr_mod.addIncludePath(imath_dep.path("src/Imath")); // for half.h with F16C support
    exr_mod.addIncludePath(b.path("")); // for our config headers

    // Link libdeflate
    exr_mod.linkLibrary(libdeflate);

    // Enable F16C for hardware half-float conversion on x86_64
    const is_x86 = target.result.cpu.arch == .x86_64 or target.result.cpu.arch == .x86;

    exr_mod.addCSourceFiles(.{
        .root = openexr_dep.path(""),
        .files = openexr_core_srcs,
        .flags = if (is_x86) &.{
            "-fPIC",
            "-Wall",
            "-std=gnu11",
            "-D_GNU_SOURCE",
            "-mf16c", // Hardware half-float conversion (F16C SSE extension)
        } else &.{
            "-fPIC",
            "-Wall",
            "-std=gnu11",
            "-D_GNU_SOURCE",
        },
    });

    // Add HT compression stubs (we don't include OpenJPH dependency)
    exr_mod.addCSourceFiles(.{
        .root = b.path(""),
        .files = &.{"internal_ht_stub.c"},
        .flags = &.{
            "-fPIC",
            "-Wall",
            "-std=gnu11",
            "-D_GNU_SOURCE",
        },
    });

    const openexr = b.addLibrary(.{
        .name = "openexr",
        .linkage = .static,
        .root_module = exr_mod,
    });

    // Install headers for downstream consumers
    openexr.installHeadersDirectory(openexr_dep.path("src/lib/OpenEXRCore"), "OpenEXR", .{
        .include_extensions = &.{".h"},
    });
    openexr.installHeader(b.path("OpenEXRConfig.h"), "OpenEXR/OpenEXRConfig.h");
    openexr.installHeader(b.path("OpenEXRConfigInternal.h"), "OpenEXR/OpenEXRConfigInternal.h");
    openexr.installHeader(b.path("ImathConfig.h"), "OpenEXR/ImathConfig.h");
    openexr.installHeader(b.path("IlmThreadConfig.h"), "OpenEXR/IlmThreadConfig.h");

    b.installArtifact(openexr);
}

const deflate_srcs: []const []const u8 = &.{
    "lib/deflate_compress.c",
    "lib/deflate_decompress.c",
    "lib/utils.c",
    "lib/adler32.c",
    "lib/crc32.c",
    "lib/zlib_compress.c",
    "lib/zlib_decompress.c",
    "lib/gzip_compress.c",
    "lib/gzip_decompress.c",
    // x86 optimizations
    "lib/x86/cpu_features.c",
};

const openexr_core_srcs: []const []const u8 = &.{
    "src/lib/OpenEXRCore/attributes.c",
    "src/lib/OpenEXRCore/base.c",
    "src/lib/OpenEXRCore/bytes.c",
    "src/lib/OpenEXRCore/channel_list.c",
    "src/lib/OpenEXRCore/chunk.c",
    "src/lib/OpenEXRCore/coding.c",
    "src/lib/OpenEXRCore/compression.c",
    "src/lib/OpenEXRCore/context.c",
    "src/lib/OpenEXRCore/debug.c",
    "src/lib/OpenEXRCore/decoding.c",
    "src/lib/OpenEXRCore/encoding.c",
    "src/lib/OpenEXRCore/float_vector.c",
    "src/lib/OpenEXRCore/internal_b44.c",
    "src/lib/OpenEXRCore/internal_b44_table.c",
    "src/lib/OpenEXRCore/internal_b44_table_init.c",
    "src/lib/OpenEXRCore/internal_dwa.c",
    "src/lib/OpenEXRCore/internal_dwa_table.c",
    "src/lib/OpenEXRCore/internal_dwa_table_init.c",
    "src/lib/OpenEXRCore/internal_huf.c",
    "src/lib/OpenEXRCore/internal_piz.c",
    "src/lib/OpenEXRCore/internal_pxr24.c",
    "src/lib/OpenEXRCore/internal_rle.c",
    "src/lib/OpenEXRCore/internal_structs.c",
    "src/lib/OpenEXRCore/internal_zip.c",
    "src/lib/OpenEXRCore/memory.c",
    "src/lib/OpenEXRCore/opaque.c",
    "src/lib/OpenEXRCore/pack.c",
    "src/lib/OpenEXRCore/parse_header.c",
    "src/lib/OpenEXRCore/part.c",
    "src/lib/OpenEXRCore/part_attr.c",
    "src/lib/OpenEXRCore/preview.c",
    "src/lib/OpenEXRCore/std_attr.c",
    "src/lib/OpenEXRCore/string.c",
    "src/lib/OpenEXRCore/string_vector.c",
    "src/lib/OpenEXRCore/unpack.c",
    "src/lib/OpenEXRCore/validation.c",
    "src/lib/OpenEXRCore/write_header.c",
};
