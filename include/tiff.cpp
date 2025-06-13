module;
#include <tiff.h>

export module tiff
    [[anonymous::autogen_file   ("lib/git/libtiff/autogen.sh")]]
    [[anonymous::configure_file ("lib/git/libtiff/configure" )]]
    [[anonymous::make_directory ("lib/git/libtiff"           )]]
    [[anonymous::update_header  ("<tiffconf.h>"              )]]
    [[anonymous::update_library ("libtiff"                   )]]
    [[anonymous::update_library ("libtiffxx"                 )]];

export
{
    
}