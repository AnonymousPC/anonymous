#pragma build "cmake -S {os.getcwd()}/third_party/git/libjpeg-turbo -B {os.getcwd()}/bin/{type}/cmake/jpeg-build --install-prefix={os.getcwd()}/bin/{type}/cmake/jpeg-install -DCMAKE_BUILD_TYPE={type} -DENABLE_SHARED=false -DENABLE_STATIC=true"
#pragma build "cmake --build   {os.getcwd()}/bin/{type}/cmake/jpeg-build -j{os.cpu_count()}"
#pragma build "cmake --install {os.getcwd()}/bin/{type}/cmake/jpeg-build"
#pragma build "cp {os.getcwd()}/bin/{type}/cmake/jpeg-install/lib*/libturbojpeg.{library_suffix} {os.getcwd()}/bin/{type}/module/jpeg.{library_suffix}" // Copy lib*/... because jpeg might install library into directories like jpeg-install/lib64 or jpeg-install/libx32.

/*
>>> cat ./third_party/git/libjpeg-turbo/CMakeLists.txt | grep option
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
*/

module;
#include <cstdio>
#include <jpeglib.h>

export module jpeg;
