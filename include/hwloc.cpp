module;
#include <hwloc.h>

export module hwloc 
#ifdef _WIN32
    [[cmake("mkdir build", "cd build", "cmake ..", "cmake --build .")]]
#elif defined(__linux__) or defined(__MACH__)
    [[make("sh autogen.sh", "sh configure", "make")]]
#endif
;

export
{

}
