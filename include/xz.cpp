module;
#undef in
#include <lzma.h>

export module xz
    [[anonymous::cmake_directory("third_party/git/xz")]]
    [[anonymous::update_library ("liblzma"           )]];