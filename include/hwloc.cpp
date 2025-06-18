module;
#include <hwloc.h>

export module hwloc 
#ifdef _WIN32
    [[anonymous::cmake_directory("third_party/git/hwloc/contrib/windows-cmake")]]
#elif defined(__linux__) or defined(__MACH__)
    [[anonymous::autogen_file   ("third_party/git/hwloc/autogen.sh")]]
    [[anonymous::configure_file ("third_party/git/hwloc/configure" )]]
    [[anonymous::make_directory ("third_party/git/hwloc"           )]]
#endif
    [[anonymous::update_header  ("<hwloc/autogen/config.h>")]]
    [[anonymous::update_library ("libhwloc.la"             )]];
