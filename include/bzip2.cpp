#if defined(__GNUC__) and not defined(__clang__)
    #pragma GCC diagnostic ignored "-Wunknown-pragmas"
#elifdef __clang__
    #pragma clang diagnostic ignored "-Wunknown-pragmas"
#elif defined(_MSC_VER) and not defined(__clang__)
    #warning "not coded yet"
#endif

#pragma build "cmake -S $anonymous/third_party/git/bzip2 -B $anonymous/bin/$type/cmake/bzip2-build --install-prefix=$anonymous/bin/$type/cmake/bzip2-install -DCMAKE_BUILD_TYPE=$type -DENABLE_APP=false -DENABLE_TESTS=false -DENABLE_DOCS=false -DENABLE_EXAMPLES=false -DENABLE_LIB_ONLY=true -DENABLE_STATIC_LIB=true -DENABLE_SHARED_LIB=false"
#pragma build "cmake --build   $anonymous/bin/$type/cmake/bzip2-build -j$parallel"
#pragma build "cmake --install $anonymous/bin/$type/cmake/bzip2-build"
#pragma build "cp $anonymous/bin/$type/cmake/bzip2-install/lib/libbz2_static.$library_suffix $anonymous/bin/$type/module/bzip2.$library_suffix"

/* 
>>> cat ./third_party/git/bzip2/CMakeOptions.txt | grep option
option(ENABLE_WERROR     "Turn on compile time warnings")
option(ENABLE_DEBUG      "Turn on debug output")
option(ENABLE_APP        "Build applications (bzip2, and bzip2recover)"
option(ENABLE_TESTS      "Build/enable unit tests."
option(ENABLE_DOCS       "Generate documentation"
option(ENABLE_EXAMPLES   "Build examples"
option(ENABLE_LIB_ONLY   "Build libbz2 only.  This is a short hand for -DENABLE_APP=0 -DENABLE_EXAMPLES=0")
option(ENABLE_STATIC_LIB "Build libbz2 in static mode also")
option(ENABLE_SHARED_LIB "Build libbz2 as a shared library" ON)
option(USE_OLD_SONAME "Use libbz2.so.1.0 for compatibility with old Makefiles" OFF)
option(ENABLE_STATIC_LIB_IS_PIC "Enable position independent code for the static library" ON)
*/

module;
#undef in
#include <bzlib.h>

export module bzip2;