module;
#include <hwloc.h>

export module hwloc 
#ifdef _WIN32
    [[anonymous::cmake_directory("lib/git/hwloc/contrib/windows-cmake")]]
#elif defined(__linux__) or defined(__MACH__)
    [[anonymous::shell_configure("lib/git/hwloc/autogen.sh")]]
    [[anonymous::shell_configure("lib/git/hwloc/configure" )]]
    [[anonymous::make_directory ("lib/git/hwloc"           )]]
#endif
    [[anonymous::update_header  ("<hwloc/autogen/config.h>")]]
    [[anonymous::update_library ("libhwloc.la"             )]];
