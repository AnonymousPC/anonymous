#pragma build "cmake --install-prefix=./bin/${type}/cmake/bzip2-install  -S ./third_party/git/bzip2 -B ./bin/${type}/cmake/bzip2-build -- -DENABLE_STATIC_LIB=ON
#pragma build 

module;
#include <bzlib.h>

export module bzip2
    [[anonymous::cmake_directory("third_party/git/bzip2", "-DENABLE_STATIC_LIB=ON")]]
    [[anonymous::update_library ("libbz2_static"                                  )]];
