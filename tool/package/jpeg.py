from module.make import *

cmake(
    name="jpeg",
    dir="./package/libjpeg-turbo",
    args=[
        "-DENABLE_SHARED=false",
        "-DENABLE_STATIC=true"
    ]
)
archieve(
    name="jpeg",
    libs=[
        "libjpeg", 
        "libturbojpeg"
    ]
)

"""
>>> cat ./package/libjpeg-turbo/CMakeLists.txt | grep option
# 3. optionally provide a way to skip the installation of libjpeg-turbo
# 4. optionally provide a way to postfix target names, to avoid namespace
option(ENABLE_SHARED "Build shared libraries" TRUE)
option(ENABLE_STATIC "Build static libraries" TRUE)
option(REQUIRE_SIMD
option(WITH_ARITH_DEC
option(WITH_ARITH_ENC
  option(WITH_JAVA
option(WITH_JPEG7
option(WITH_JPEG8
option(WITH_SIMD "Include SIMD extensions, if available for this platform" TRUE)
option(WITH_TURBOJPEG
option(WITH_FUZZ "Build fuzz targets" FALSE)
macro(report_option var desc)
report_option(ENABLE_SHARED "Shared libraries")
report_option(ENABLE_STATIC "Static libraries")
report_option(WITH_ARITH_DEC "Arithmetic decoding support")
report_option(WITH_ARITH_ENC "Arithmetic encoding support")
report_option(WITH_TURBOJPEG "TurboJPEG API library")
report_option(WITH_JAVA "TurboJPEG Java wrapper")
  option(WITH_CRT_DLL
option(FORCE_INLINE "Force function inlining" TRUE)
# depending on the compiler and compiler options.  We leave it to the user to
# depending on the compiler and compiler options.  We leave it to the user to
"""

"""
>>> cat ./package/libjpeg-turbo/CMakeLists.txt | grep CMAKE_INSTALL_DEFAULT_LIBDIR
      set(CMAKE_INSTALL_DEFAULT_LIBDIR "lib64")
      set(CMAKE_INSTALL_DEFAULT_LIBDIR "libx32")
      set(CMAKE_INSTALL_DEFAULT_LIBDIR "lib32")
"""