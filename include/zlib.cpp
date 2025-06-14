module;
#undef in
#include <zlib.h>

export module zlib
    [[anonymous::cmake_directory("third_party/git/zlib")]]
    [[anonymous::update_library ("libz"        )]];
