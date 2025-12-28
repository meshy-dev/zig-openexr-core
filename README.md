# zig-openexr-core

Zig build system for [OpenEXR Core](https://openexr.com/en/latest/OpenEXRCoreAPI.html) - the pure C API for reading and writing OpenEXR files.

> **NOTE:** This build system conversion from CMake to Zig involved significant AI/LLM assistance. Please review `build.zig` to verify correctness for your use case.

## Features

- **Pure C API** - No C++ dependencies, suitable for FFI/bindings
- **Full compression support** - ZIP, ZIPS, RLE, PIZ, PXR24, B44, DWA
- **F16C SIMD acceleration** - Hardware half-float conversion on x86_64
- **Cross-platform** - Builds with Zig's cross-compilation support

## Building

```bash
# Debug build
zig build

# Release build
zig build -Doptimize=ReleaseFast

# Cross-compile example
zig build -Dtarget=x86_64-linux-musl -Doptimize=ReleaseFast
```

## Output

- `zig-out/lib/libopenexr.a` - Static library (includes libdeflate)
- `zig-out/include/OpenEXR/` - OpenEXR Core headers

## Limitations

- **JPEG-HT compression** - Returns `EXR_ERR_FEATURE_NOT_IMPLEMENTED` (requires OpenJPH C++ library)

## Dependencies

All dependencies are fetched automatically via Zig's package manager:

| Dependency | Version | License |
|------------|---------|---------|
| [OpenEXR](https://github.com/AcademySoftwareFoundation/openexr) | 3.4.4 | [BSD-3-Clause](LICENSE-OPENEXR) |
| [libdeflate](https://github.com/ebiggers/libdeflate) | 1.23 | [MIT](LICENSE-LIBDEFLATE) |
| [Imath](https://github.com/AcademySoftwareFoundation/Imath) | 3.2.1 | [BSD-3-Clause](LICENSE-OPENEXR) |

## License

- Build scripts (`build.zig`, `build.zig.zon`, config headers): [MIT](LICENSE)
- OpenEXR and Imath: [BSD-3-Clause](LICENSE-OPENEXR)
- libdeflate: [MIT](LICENSE-LIBDEFLATE)
