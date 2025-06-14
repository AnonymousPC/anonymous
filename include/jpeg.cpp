module;
#include <cstdio>
#include <jpeglib.h>

export module jpeg 
    [[anonymous::cmake_directory("third_party/git/libjpeg-turbo")]]
    [[anonymous::update_header  ("<jconfig.h>"          )]]
    [[anonymous::update_library ("libturbojpeg"         )]];
