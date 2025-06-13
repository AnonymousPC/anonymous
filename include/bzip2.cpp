module;
#include <bzlib.h>

export module bzip2
    [[anonymous::cmake_directory("lib/git/bzip2", "-DENABLE_LIB_ONLY=ON", "-DENABLE_SHARED_LIB=OFF", "-DENABLE_DOCS=OFF")]];
