module;
#include <zstd.h>

export module zstd
    [[anonymous::cmake_directory("third_party/git/zstd/build/cmake")]]
    [[anonymous::update_library ("libzstd"                 )]];
