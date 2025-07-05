from module.make import *

cmake(
    name="zstd",
    dir="./package/zstd/build/cmake",
    args=[
        "-DZSTD_BUILD_PROGRAMS=false",
        "-DZSTD_BUILD_CONTRIB=false",
        "-DZSTD_BUILD_TESTS=false",
        "-DZSTD_BUILD_STATIC=true",
        "-DZSTD_BUILD_SHARED=false"
    ]
)
archieve(
    name="zstd",
    libs=["libzstd"]
)

"""
>>> find ./package/zstd/build/cmake -type f | xargs -I {file} sh -c "cat {file} | grep option | xargs -I {line} echo {file}: {line}"
./package/zstd/build/cmake/CMakeModules/ZstdOptions.cmake: option(ZSTD_LEGACY_SUPPORT Enable legacy format support ON)
./package/zstd/build/cmake/CMakeModules/ZstdOptions.cmake: # Platform-specific options
./package/zstd/build/cmake/CMakeModules/ZstdOptions.cmake: option(ZSTD_FRAMEWORK Build as Apple Framework OFF)
./package/zstd/build/cmake/CMakeModules/ZstdOptions.cmake: option(ZSTD_MULTITHREAD_SUPPORT Enable multi-threading support ${ZSTD_MULTITHREAD_SUPPORT_DEFAULT})
./package/zstd/build/cmake/CMakeModules/ZstdOptions.cmake: # Build component options
./package/zstd/build/cmake/CMakeModules/ZstdOptions.cmake: option(ZSTD_BUILD_PROGRAMS Build command-line programs ON)
./package/zstd/build/cmake/CMakeModules/ZstdOptions.cmake: option(ZSTD_BUILD_CONTRIB Build contrib utilities OFF)
./package/zstd/build/cmake/CMakeModules/ZstdOptions.cmake: option(ZSTD_PROGRAMS_LINK_SHARED Link programs against shared library OFF)
./package/zstd/build/cmake/CMakeModules/ZstdOptions.cmake: option(ZSTD_BUILD_TESTS Build test suite ${ZSTD_BUILD_TESTS_default})
./package/zstd/build/cmake/CMakeModules/ZstdOptions.cmake: # MSVC-specific options
./package/zstd/build/cmake/CMakeModules/ZstdOptions.cmake: option(ZSTD_USE_STATIC_RUNTIME Link to static runtime libraries OFF)
./package/zstd/build/cmake/CMakeModules/ZstdBuild.cmake: # Always build the library first (this defines ZSTD_BUILD_STATIC/SHARED options)
./package/zstd/build/cmake/CMakeModules/ZstdBuild.cmake: # Validate build configuration after lib options are defined
./package/zstd/build/cmake/lib/CMakeLists.txt: option(ZSTD_BUILD_STATIC BUILD STATIC LIBRARIES ON)
./package/zstd/build/cmake/lib/CMakeLists.txt: option(ZSTD_BUILD_SHARED BUILD SHARED LIBRARIES ON)
./package/zstd/build/cmake/lib/CMakeLists.txt: option(ZSTD_BUILD_COMPRESSION BUILD COMPRESSION MODULE ON)
./package/zstd/build/cmake/lib/CMakeLists.txt: option(ZSTD_BUILD_DECOMPRESSION BUILD DECOMPRESSION MODULE ON)
./package/zstd/build/cmake/lib/CMakeLists.txt: option(ZSTD_BUILD_DICTBUILDER BUILD DICTBUILDER MODULE ON)
./package/zstd/build/cmake/lib/CMakeLists.txt: option(ZSTD_BUILD_DEPRECATED BUILD DEPRECATED MODULE OFF)
./package/zstd/build/cmake/lib/CMakeLists.txt: add_compile_options(-DZSTD_DISABLE_ASM)
./package/zstd/build/cmake/lib/CMakeLists.txt: add_compile_options(-DZSTD_DISABLE_ASM)
./package/zstd/build/cmake/tests/CMakeLists.txt: # default_value: Value to initialize the option with. Can be space separated.
./package/zstd/build/cmake/tests/CMakeLists.txt: target_compile_options(fullbench PRIVATE -Wno-deprecated-declarations)
./package/zstd/build/cmake/tests/CMakeLists.txt: target_compile_options(fuzzer PRIVATE -Wno-deprecated-declarations)
./package/zstd/build/cmake/tests/CMakeLists.txt: target_compile_options(zstreamtest PRIVATE -Wno-deprecated-declarations)
./package/zstd/build/cmake/CMakeLists.txt: # Configure build options
./package/zstd/build/cmake/programs/CMakeLists.txt: option(ZSTD_ZLIB_SUPPORT ZLIB SUPPORT OFF)
./package/zstd/build/cmake/programs/CMakeLists.txt: option(ZSTD_LZMA_SUPPORT LZMA SUPPORT OFF)
./package/zstd/build/cmake/programs/CMakeLists.txt: option(ZSTD_LZ4_SUPPORT LZ4 SUPPORT OFF)
./package/zstd/build/cmake/README.md: To show cmake build options, you can:
./package/zstd/build/cmake/README.md: Bool options can be set to `ON/OFF` with `-D[option]=[ON/OFF]`. You can configure cmake options like this:
./package/zstd/build/cmake/README.md: For all options available, you can see it on <https://github.com/facebook/zstd/blob/dev/build/cmake/lib/CMakeLists.txt>
"""