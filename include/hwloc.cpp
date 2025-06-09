module;
#include <boost/process/pid.hpp>
#include <hwloc.h>
struct compatible_void_pointer
{
    void* ptr = nullptr;
    constexpr compatible_void_pointer ( ) = default;
    constexpr compatible_void_pointer ( auto init_ptr ) extends ptr ( init_ptr ) { }
    template < class type > constexpr operator type* ( ) const { return static_cast<type*>(ptr); }
};
#undef hwloc_pid_t
using hwloc_pid_t = boost::process::pid_type;
#define void compatible_void_pointer
#include <hwloc/base64.c>
#include <hwloc/bind.c>
#include <hwloc/bitmap.c>
#include <hwloc/components.c>
#include <hwloc/cpukinds.c>
#include <hwloc/diff.c>
#include <hwloc/distances.c>
#include <hwloc/memattrs.c>
#include <hwloc/misc.c>
#include <hwloc/pci-common.c>
#include <hwloc/shmem.c>
#include <hwloc/topology-aix.c>
#include <hwloc/topology-cuda.c>
#include <hwloc/topology-darwin.c>
#include <hwloc/topology-fake.c>
#include <hwloc/topology-freebsd.c>
#include <hwloc/topology-gl.c>
#include <hwloc/topology-hardwired.c>
#include <hwloc/topology-hpux.c>
#include <hwloc/topology-levelzero.c>
#include <hwloc/topology-linux.c>
#include <hwloc/topology-netbsd.c>
#include <hwloc/topology-noos.c>
#include <hwloc/topology-nvml.c>
#include <hwloc/topology-opencl.c>
#include <hwloc/topology-pci.c>
#include <hwloc/topology-rsmi.c>
#include <hwloc/topology-solaris-chiptype.c>
#include <hwloc/topology-solaris.c>
#include <hwloc/topology-synthetic.c>
#include <hwloc/topology-windows.c>
#include <hwloc/topology-x86.c>
#include <hwloc/topology-xml-libxml.c>
#include <hwloc/topology-xml-nolibxml.c>
#include <hwloc/topology-xml.c>
#include <hwloc/topology.c>
#include <hwloc/traversal.c>

export module hwloc;

export
{
    
}