module;
#include <tiff.h>

export module tiff
    [[anonymous::cmake_directory("lib/git/libtiff")]]
    [[anonymous::update_header  ("<tiffconf.h>"   )]]
    [[anonymous::update_library ("libtiff"        )]]
    [[anonymous::update_library ("libtiffxx"      )]];

export
{
    
}