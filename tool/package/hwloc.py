from module.make import *

if system == "windows":
    cmake(
        name="hwloc",
        dir="./package/hwloc/contrib/windows-cmake",
        args=[
            "-DHWLOC_ENABLE_TESTING=false",
            "-DHWLOC_SKIP_LSTOPO=true",
            "-DHWLOC_SKIP_TOOLS=true",
            "-DHWLOC_SKIP_INCLUDES=false",
            "-DHWLOC_BUILD_SHARED_LIBS=false"
        ]
    )
elif system == "linux" or system == "macos":
    autogen(
        name="hwloc",
        file="./package/hwloc/autogen.sh"
    )
    configure(
        name="hwloc",
        file="./package/hwloc/configure",
        args=[
            "--enable-static",
            "--disable-shared",
            "--enable-debug" if type == "debug" else "",
            "--disable-readme"
        ]
    )
    make(
        name="hwloc",
        dir="./third_aprty/hwloc"
    )
archieve(
    name="hwloc",
    libs=["libhwloc"]
)
    
""" 
>>> cat ./package/hwloc/contrib/windows-cmake/CMakeLists.txt | grep option
option(HWLOC_ENABLE_TESTING "Enable testing" ON)
option(HWLOC_SKIP_LSTOPO "don't build/install lstopo")
option(HWLOC_SKIP_TOOLS "don't build/install other hwloc tools")
option(HWLOC_SKIP_INCLUDES "don't install headers")
option(HWLOC_WITH_LIBXML2 "use libxml2 instead of minimal XML")
option(HWLOC_WITH_OPENCL "enable OpenCL support")
    option(HWLOC_WITH_CUDA "enable CUDA support")
option(HWLOC_BUILD_SHARED_LIBS "build shared libraries" ${BUILD_SHARED_LIBS})
# --- optional external libraries
    target_link_options(lstopo-win PRIVATE "$<$<BOOL:${MSVC}>:/subsystem:windows;/entry:mainCRTStartup>")
"""

"""
>>> ./package/hwloc/configure -h | grep -E 'enable|disable'
      --cache-file=FILE   cache test results in FILE [disabled]
  --disable-option-checking  ignore unrecognized --enable/--with options
  --disable-FEATURE       do not include FEATURE (same as --enable-FEATURE=no)
  --enable-FEATURE[=ARG]  include FEATURE [ARG=yes]
  --enable-silent-rules   less verbose build output (undo: "make V=1")
  --disable-silent-rules  verbose build output (undo: "make V=0")
  --enable-dependency-tracking
  --disable-dependency-tracking
  --enable-shared[=PKGS]  build shared libraries [default=yes]
  --enable-static[=PKGS]  build static libraries [default=no]
  --enable-pic[=PKGS]     try to use only PIC/non-PIC objects [default=use
  --enable-cxx-stdlib[=PKGS]
  --enable-fast-install[=PKGS]
  --enable-aix-soname=aix|svr4|both
  --disable-libtool-lock  avoid locking (might break parallel builds)
  --enable-embedded-mode  Using --enable-embedded-mode puts the HWLOC into
                          --disable-embedded-mode, meaning that the HWLOC is
  --enable-debug          Using --enable-debug enables various hwloc
  --enable-doxygen        enable support for building Doxygen documentation
  --disable-readme        disable the updating of the top-level README file
  --disable-picky         When in developer checkouts of hwloc and compiling
                          with gcc, the default is to enable maximum compiler
                          pickyness. Using --disable-picky or --enable-picky
  --disable-cairo         Disable the Cairo back-end of hwloc's lstopo command
  --disable-cpuid         Disable the cpuid-based architecture specific
  --disable-libxml2       Do not use libxml2 for XML support, use a custom
  --disable-io            Disable I/O discovery build entirely (PCI, LinuxIO,
  --disable-pci           Disable the PCI device discovery build (instead of
  --disable-opencl        Disable the OpenCL device discovery build (instead
  --disable-cuda          Disable the CUDA device discovery build using
  --disable-nvml          Disable the NVML device discovery build (instead of
  --disable-rsmi          Disable the ROCm SMI device discovery
  --disable-levelzero     Disable the oneAPI Level Zero device discovery
  --disable-gl            Disable the GL display device discovery (instead of
  --disable-libudev       Disable the Linux libudev
  --enable-plugins=name,...
  --disable-plugin-dlopen Do not use dlopen for loading plugins.
  --disable-plugin-ltdl   Do not use ltdl for loading plugins.
  --enable-visibility     enable visibility feature of certain
                          compilers/linkers (default: enabled on platforms
                          CUDA are disabled (CUDA, NVML and NVIDIA OpenCL).
"""