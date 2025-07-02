from module.make import *

cmake(
    module_name="lz4",
    dir="./third_party/lz4/build/cmake",
    args=[
        "-DLZ4_BUILD_CLI=false",
        "-DLZ4_BUILD_LEGACY_LZ4C=false",
        "-DBUILD_SHARED_LIBS=false",
        "-DBUILD_STATIC_LIBS=true"
    ]
)

"""
>>> cat ./third_party/lz4/build/cmake/CMakeLists.txt | grep -i option
# BUILD OPTIONS - Configure build targets and features
option(LZ4_BUILD_CLI "Build lz4 program" ON)
option(LZ4_BUILD_LEGACY_LZ4C "Build lz4c program with legacy argument support" OFF)
# via the BUILD_SHARED_LIBS option unless we are in bundled mode, in
include(CMakeDependentOption)
CMAKE_DEPENDENT_OPTION(BUILD_SHARED_LIBS "Build shared libraries" ON "NOT LZ4_BUNDLED_MODE" OFF)
CMAKE_DEPENDENT_OPTION(BUILD_STATIC_LIBS "Build static libraries" OFF "BUILD_SHARED_LIBS" ON)
option(LZ4_POSITION_INDEPENDENT_LIB "Use position independent code for static library (if applicable)" ${LZ4_POSITION_INDEPENDENT_LIB_DEFAULT})
  set_target_properties(lz4c PROPERTIES COMPILE_DEFINITIONS "ENABLE_LZ4C_LEGACY_OPTIONS")
# COMPILER FLAGS - Configure warning flags and compiler-specific options
# """