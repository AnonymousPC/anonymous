module;
#include <zstd.h>

export module zstd
    [[anonymous::cmake_directory("lib/git/zstd/build/cmake")]]
    [[anonymous::update_library ("libzstd"                 )]];
