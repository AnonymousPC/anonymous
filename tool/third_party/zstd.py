from module.make import *

cmake(
    export_name="zstd",
    dir="./third_party/zstd/build/cmake",
    args=[
        "-DZSTD_MULTITHREAD_SUPPORT=true",
        "-DZSTD_BUILD_PROGRAMS=false",
        "-DZSTD_BUILD_CONTRIB=false",
        "-DZSTD_BUILD_TESTS=false",
        "-DZSTD_BUILD_STATIC=true",
        "-DZSTD_BUILD_SHARED=false",
        "-DZSTD_ZLIB_SUPPORT=true",
        "-DZSTD_LZMA_SUPPORT=true",
        "-DZSTD_LZ4_SUPPORT=fa;se"
    ]
)

"""
>>> find ./third_party/zstd/build/cmake -type f | xargs cat | rg "option\("
option(ZSTD_LEGACY_SUPPORT "Enable legacy format support" ON)
    option(ZSTD_FRAMEWORK "Build as Apple Framework" OFF)
option(ZSTD_MULTITHREAD_SUPPORT "Enable multi-threading support" ${ZSTD_MULTITHREAD_SUPPORT_DEFAULT})
option(ZSTD_BUILD_PROGRAMS "Build command-line programs" ON)
option(ZSTD_BUILD_CONTRIB "Build contrib utilities" OFF)
option(ZSTD_PROGRAMS_LINK_SHARED "Link programs against shared library" OFF)
option(ZSTD_BUILD_TESTS "Build test suite" ${ZSTD_BUILD_TESTS_default})
    option(ZSTD_USE_STATIC_RUNTIME "Link to static runtime libraries" OFF)
option(ZSTD_BUILD_STATIC "BUILD STATIC LIBRARIES" ON)
option(ZSTD_BUILD_SHARED "BUILD SHARED LIBRARIES" ON)
option(ZSTD_BUILD_COMPRESSION "BUILD COMPRESSION MODULE" ON)
option(ZSTD_BUILD_DECOMPRESSION "BUILD DECOMPRESSION MODULE" ON)
option(ZSTD_BUILD_DICTBUILDER "BUILD DICTBUILDER MODULE" ON)
option(ZSTD_BUILD_DEPRECATED "BUILD DEPRECATED MODULE" OFF)
option(ZSTD_ZLIB_SUPPORT "ZLIB SUPPORT" OFF)
option(ZSTD_LZMA_SUPPORT "LZMA SUPPORT" OFF)
option(ZSTD_LZ4_SUPPORT "LZ4 SUPPORT" OFF)
"""