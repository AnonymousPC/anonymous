from module.make import *

cmake(
    name="png",
    dir="./package/libpng",
    args=[
        "-DPNG_SHARED=false",
        "-DPNG_STATIC=true",
        "-DPNG_TESTS=false",
        "-DPNG_TOOLS=false"
    ]
)
archieve(
    name="png",
    libs=["libpng"]
)

"""
>>> cat ./package/libpng/CMakeLists.txt | grep option
  message(SEND_ERROR "The options DFA_XTRA=\"${DFA_XTRA}\" "
option(PNG_SHARED "Build libpng as a shared library" ON)
option(PNG_STATIC "Build libpng as a static library" ON)
  option(PNG_FRAMEWORK "Build libpng as a framework bundle" ON)
  option(PNG_FRAMEWORK "Build libpng as a framework bundle (not available on this platform)" OFF)
  message(SEND_ERROR "The option PNG_FRAMEWORK should not be set on this platform")
option(PNG_TESTS "Build the libpng tests" ON)
# the users are allowed to override the option to build by default.
  option(PNG_TOOLS "Build the libpng tools" OFF)
  option(PNG_TOOLS "Build the libpng tools" ON)
# Maintain backwards compatibility with the deprecated option PNG_EXECUTABLES.
option(PNG_EXECUTABLES "[Deprecated; please use PNG_TOOLS]" ON)
  message(DEPRECATION "The option PNG_EXECUTABLES has been deprecated in favour of PNG_TOOLS")
option(PNG_HARDWARE_OPTIMIZATIONS "Enable hardware optimizations" ON)
# With CMake 3.12 and newer, this option is no longer necessary.
option(PNG_BUILD_ZLIB "[Deprecated; please use ZLIB_ROOT]" OFF)
    message(SEND_ERROR "The option PNG_BUILD_ZLIB=${PNG_BUILD_ZLIB} is no longer supported; "
    message(SEND_ERROR "The option PNG_BUILD_ZLIB=${PNG_BUILD_ZLIB} is no longer supported; "
        message(FATAL_ERROR "This compiler does not support the -mlsx option")
option(ld-version-script "Enable linker version script" ON)
  # from our DFA files and (optionally) out of the user-supplied DFA file.
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/scripts/options.awk"
                 "${CMAKE_CURRENT_BINARY_DIR}/scripts/options.awk"
                          "${CMAKE_CURRENT_BINARY_DIR}/scripts/options.awk"
                          "${CMAKE_CURRENT_BINARY_DIR}/scripts/options.awk"
                     "Please enable at least one of the following options: "
"""