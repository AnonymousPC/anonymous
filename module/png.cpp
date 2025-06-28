module;
#undef in
#include <png.h>

export module png;
import zlib;
    [[anonymous::cmake_directory("third_party/git/libpng")]] 
    [[anonymous::update_header  ("<pngconf.h>"   )]]
    [[anonymous::update_header  ("<pnglibconf.h>")]]
    [[anonymous::update_library ("libpng"        )]];
 

