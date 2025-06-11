module;
#include <hwloc.h>

export module hwloc 
#ifdef _WIN32
    [[cmake("lib/git/hwloc/contrib/windows-cmake")]]
#elif defined(__linux__) or defined(__MACH__)
    [[autogen("lib/git/hwloc"), configure("lib/git/hwloc"), make("lib/git/hwloc")]]
#endif
    [[cp("<hwloc/autogen/config.h>")]];

export
{

}
