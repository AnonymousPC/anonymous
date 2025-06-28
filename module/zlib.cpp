#pragma build "cmake -S {os.getcwd()}/third_party/git/zlib -B {os.getcwd()}/bin/{type}/cmake/zlib-build --install-prefix={os.getcwd()}/bin/{type}/cmake/zlib-install -DCMAKE_BUILD_TYPE={type} -DZLIB_BUILD_TESTING=false -DZLIB_BUILD_SHARED=false -DZLIB_BUILD_STATIC=true -DZLIB_BUILD_MINIZIP=false"
#pragma build "cmake --build   {os.getcwd()}/bin/{type}/cmake/zlib-build -j{os.cpu_count()}"
#pragma build "cmake --install {os.getcwd()}/bin/{type}/cmake/zlib-build"
#pragma build "cp {os.getcwd()}/bin/{type}/cmake/zlib-install/lib/libz.{library_suffix} {os.getcwd()}/bin/{type}/module/zlib.{library_suffix}"

/*
>>> cat ./third_party/git/zlib/CMakeLists.txt | grep option
option(ZLIB_BUILD_TESTING "Enable Zlib Examples as tests" ON)
option(ZLIB_BUILD_SHARED "Enable building zlib shared library" ON)
option(ZLIB_BUILD_STATIC "Enable building zlib static library" ON)
option(ZLIB_BUILD_MINIZIP "Enable building libminizip contrib library" OFF)
option(ZLIB_INSTALL "Enable installation of zlib" ON)
option(ZLIB_PREFIX "prefix for all types and library functions, see zconf.h.in"
    option(ZLIB_INSTALL_COMPAT_DLL "Install a copy as zlib1.dll" ON)
*/


module;
#undef in
#include <zlib.h>

export module zlib;
