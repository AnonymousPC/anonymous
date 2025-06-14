module;
#include <bzlib.h>

export module bzip2
    [[anonymous::cmake_directory("third_party/git/bzip2")]]
    [[anonymous::update_library ("libbz2"       )]];
