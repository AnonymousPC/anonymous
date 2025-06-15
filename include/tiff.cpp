module;
#include <tiff.h>

export module tiff
    [[anonymous::autogen_file   ("third_party/git/libtiff/autogen.sh")]]
    [[anonymous::configure_file ("third_party/git/libtiff/configure" )]]
    [[anonymous::make_directory ("third_party/git/libtiff"           )]]
    [[anonymous::update_header  ("<tiffconf.h>"                      )]]
    [[anonymous::update_library ("libtiff"                           )]]
    [[anonymous::update_library ("libtiffxx"                         )]];

export
{
    
}