module;
#undef in
#include <zlib.h>

export module zlib
    [[anonymous::cmake_directory("lib/git/zlib")]]
    [[anonymous::update_library ("libz"        )]];
