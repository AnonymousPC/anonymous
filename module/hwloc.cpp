module;
#include <hwloc.h>
#ifdef _WIN32
    #define MAKE                                                       \
        anonymous::cmake_directory                                     \
        (                                                              \
            "./third_party/git/hwloc/contrib/windows-cmake",           \
            "-DHWLOC_ENABLE_TESTING=false",                            \
            "-DHWLOC_SKIP_LSTOPO=true",                                \
            "-DHWLOC_SKIP_TOOLS=true",                                 \
            "-DHWLOC_BUILD_SHARED_LIBS=false"                          \
        )
#elif defined(__linux__) or defined(__MACH__)
    #define MAKE                                                       \
        anonymous::autogen_file("./third_party/git/hwloc/autogen.sh"), \
        anonymous::configure_file                                      \
        (                                                              \
            "./third_party/git/hwloc/configure",                       \
            "--enable-static",                                         \
            "--disable-shared",                                        \
            "--disable-readme"                                         \
        ),                                                             \
        anonymous::make_directory("./third_party/git/hwloc")
#endif

export module hwloc                                      \
[[                                                       \
    anonymous::cmake_if(..., _WIN32),                                                \
    anonymous::update_header ("hwloc/autogen/config.h"), \
    anonymous::update_library("libhwloc", "hwloc")       \
]];

/* 
>>> cat ./third_party/git/hwloc/contrib/windows-cmake/CMakeLists.txt | grep option
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
*/

/* 
>>>./third_party/git/hwloc/configure -h
'configure' configures hwloc 3.0.0a1-git to adapt to many kinds of systems.

Usage: ./third_party/git/hwloc/configure [OPTION]... [VAR=VALUE]...

To assign environment variables (e.g., CC, CFLAGS...), specify them as
VAR=VALUE.  See below for descriptions of some of the useful variables.

Defaults for the options are specified in brackets.

Configuration:
  -h, --help              display this help and exit
      --help=short        display options specific to this package
      --help=recursive    display the short help of all the included packages
  -V, --version           display version information and exit
  -q, --quiet, --silent   do not print 'checking ...' messages
      --cache-file=FILE   cache test results in FILE [disabled]
  -C, --config-cache      alias for '--cache-file=config.cache'
  -n, --no-create         do not create output files
      --srcdir=DIR        find the sources in DIR [configure dir or '..']

Installation directories:
  --prefix=PREFIX         install architecture-independent files in PREFIX
                          [/usr/local]
  --exec-prefix=EPREFIX   install architecture-dependent files in EPREFIX
                          [PREFIX]

By default, 'make install' will install all the files in
'/usr/local/bin', '/usr/local/lib' etc.  You can specify
an installation prefix other than '/usr/local' using '--prefix',
for instance '--prefix=$HOME'.

For better control, use the options below.

Fine tuning of the installation directories:
  --bindir=DIR            user executables [EPREFIX/bin]
  --sbindir=DIR           system admin executables [EPREFIX/sbin]
  --libexecdir=DIR        program executables [EPREFIX/libexec]
  --sysconfdir=DIR        read-only single-machine data [PREFIX/etc]
  --sharedstatedir=DIR    modifiable architecture-independent data [PREFIX/com]
  --localstatedir=DIR     modifiable single-machine data [PREFIX/var]
  --runstatedir=DIR       modifiable per-process data [LOCALSTATEDIR/run]
  --libdir=DIR            object code libraries [EPREFIX/lib]
  --includedir=DIR        C header files [PREFIX/include]
  --oldincludedir=DIR     C header files for non-gcc [/usr/include]
  --datarootdir=DIR       read-only arch.-independent data root [PREFIX/share]
  --datadir=DIR           read-only architecture-independent data [DATAROOTDIR]
  --infodir=DIR           info documentation [DATAROOTDIR/info]
  --localedir=DIR         locale-dependent data [DATAROOTDIR/locale]
  --mandir=DIR            man documentation [DATAROOTDIR/man]
  --docdir=DIR            documentation root [DATAROOTDIR/doc/hwloc]
  --htmldir=DIR           html documentation [DOCDIR]
  --dvidir=DIR            dvi documentation [DOCDIR]
  --pdfdir=DIR            pdf documentation [DOCDIR]
  --psdir=DIR             ps documentation [DOCDIR]

Program names:
  --program-prefix=PREFIX            prepend PREFIX to installed program names
  --program-suffix=SUFFIX            append SUFFIX to installed program names
  --program-transform-name=PROGRAM   run sed PROGRAM on installed program names

X features:
  --x-includes=DIR    X include files are in DIR
  --x-libraries=DIR   X library files are in DIR

System types:
  --build=BUILD     configure for building on BUILD [guessed]
  --host=HOST       cross-compile to build programs to run on HOST [BUILD]
  --target=TARGET   configure for building compilers for TARGET [HOST]

Optional Features:
  --disable-option-checking  ignore unrecognized --enable/--with options
  --disable-FEATURE       do not include FEATURE (same as --enable-FEATURE=no)
  --enable-FEATURE[=ARG]  include FEATURE [ARG=yes]
  --enable-silent-rules   less verbose build output (undo: "make V=1")
  --disable-silent-rules  verbose build output (undo: "make V=0")
  --enable-dependency-tracking
                          do not reject slow dependency extractors
  --disable-dependency-tracking
                          speeds up one-time build
  --enable-shared[=PKGS]  build shared libraries [default=yes]
  --enable-static[=PKGS]  build static libraries [default=no]
  --enable-pic[=PKGS]     try to use only PIC/non-PIC objects [default=use
                          both]
  --enable-fast-install[=PKGS]
                          optimize for fast installation [default=yes]
  --enable-aix-soname=aix|svr4|both
                          shared library versioning (aka "SONAME") variant to
                          provide on AIX, [default=aix].
  --disable-libtool-lock  avoid locking (might break parallel builds)
  --enable-embedded-mode  Using --enable-embedded-mode puts the HWLOC into
                          "embedded" mode. The default is
                          --disable-embedded-mode, meaning that the HWLOC is
                          in "standalone" mode.
  --enable-debug          Using --enable-debug enables various hwloc
                          maintainer-level debugging controls. This option is
                          not recomended for end users.
  --enable-doxygen        enable support for building Doxygen documentation
                          (note that this option is ONLY relevant in developer
                          builds; Doxygen documentation is pre-built for
                          tarball builds and this option is therefore ignored)
  --disable-readme        disable the updating of the top-level README file
                          from the HTML documentation index
  --disable-picky         When in developer checkouts of hwloc and compiling
                          with gcc, the default is to enable maximum compiler
                          pickyness. Using --disable-picky or --enable-picky
                          overrides any default setting
  --disable-cairo         Disable the Cairo back-end of hwloc's lstopo command
  --disable-cpuid         Disable the cpuid-based architecture specific
                          support (x86 component)
  --disable-libxml2       Do not use libxml2 for XML support, use a custom
                          minimalistic support
  --disable-io            Disable I/O discovery build entirely (PCI, LinuxIO,
                          CUDA, OpenCL, NVML, RSMI, LevelZero, GL) instead of
                          only disabling it at runtime by default
  --disable-pci           Disable the PCI device discovery build (instead of
                          only disabling PCI at runtime by default)
  --disable-opencl        Disable the OpenCL device discovery build (instead
                          of only disabling OpenCL at runtime by default)
  --disable-cuda          Disable the CUDA device discovery build using
                          libcudart (instead of only disabling CUDA at runtime
                          by default)
  --disable-nvml          Disable the NVML device discovery build (instead of
                          only disabling NVML at runtime by default)
  --disable-rsmi          Disable the ROCm SMI device discovery
  --disable-levelzero     Disable the oneAPI Level Zero device discovery
  --disable-gl            Disable the GL display device discovery (instead of
                          only disabling GL at runtime by default)
  --disable-libudev       Disable the Linux libudev
  --enable-plugins=name,...
                          Build the given components as dynamically-loaded
                          plugins
  --disable-plugin-dlopen Do not use dlopen for loading plugins.
  --disable-plugin-ltdl   Do not use ltdl for loading plugins.
  --enable-visibility     enable visibility feature of certain
                          compilers/linkers (default: enabled on platforms
                          that support it)

Optional Packages:
  --with-PACKAGE[=ARG]    use PACKAGE [ARG=yes]
  --without-PACKAGE       do not use PACKAGE (same as --with-PACKAGE=no)
  --with-gnu-ld           assume the C compiler uses GNU ld [default=no]
  --with-sysroot[=DIR]    Search for dependent libraries within DIR (or the
                          compiler's sysroot if not specified).
  --with-hwloc-symbol-prefix=STRING
                          STRING can be any valid C symbol name. It will be
                          prefixed to all public HWLOC symbols. Default: ""
                          (no prefix)
  --with-cuda-version=<version>
                          Specify the CUDA version (e.g. 11.2) for selecting
                          the appropriate pkg-config file
  --with-cuda=<dir>       Specify the CUDA installation directory, used for
                          NVIDIA NVML and OpenCL too. If a non-existent
                          directory is given, all dependencies installed by
                          CUDA are disabled (CUDA, NVML and NVIDIA OpenCL).
  --with-rocm-version=<version>
                          Specify the ROCm version (e.g. 4.2.0) for selecting
                          the default ROCm installation path (e.g.
                          /opt/rocm-4.2.0)
  --with-rocm=<dir>       Specify the ROCm installation directory
  --with-hwloc-plugins-path=dir:...
                          Colon-separated list of plugin directories. Default:
                          "$prefix/lib/hwloc". Plugins will be installed in
                          the first directory. They will be loaded from all of
                          them, in order.
  --with-x                use the X Window System

Some influential environment variables:
  CC          C compiler command
  CFLAGS      C compiler flags
  LDFLAGS     linker flags, e.g. -L<lib dir> if you have libraries in a
              nonstandard directory <lib dir>
  LIBS        libraries to pass to the linker, e.g. -l<library>
  CPPFLAGS    (Objective) C/C++ preprocessor flags, e.g. -I<include dir> if
              you have headers in a nonstandard directory <include dir>
  LT_SYS_LIBRARY_PATH
              User-defined run-time library search path.
  CXX         C++ compiler command
  CXXFLAGS    C++ compiler flags
  CXXCPP      C++ preprocessor
  HWLOC_MS_LIB
              Path to Microsoft's Visual Studio `lib' tool
  CUDA_VERSION
              The CUDA version (e.g. 11.2) for selecting the appropriate
              pkg-config file
  ROCM_VERSION
              The ROCm version (e.g. 4.2.0) for selecting the default ROCm
              installation path (e.g. /opt/rocm-4.2.0)
  PKG_CONFIG  path to pkg-config utility
  HWLOC_PCIACCESS_CFLAGS
              C compiler flags for PCIACCESS, overriding pkg-config
  HWLOC_PCIACCESS_LIBS
              linker flags for PCIACCESS, overriding pkg-config
  HWLOC_CUDA_CFLAGS
              C compiler flags for CUDA, overriding pkg-config
  HWLOC_CUDA_LIBS
              linker flags for CUDA, overriding pkg-config
  HWLOC_CUDART_CFLAGS
              C compiler flags for CUDART, overriding pkg-config
  HWLOC_CUDART_LIBS
              linker flags for CUDART, overriding pkg-config
  HWLOC_LEVELZERO_CFLAGS
              C compiler flags for LEVELZERO, overriding pkg-config
  HWLOC_LEVELZERO_LIBS
              linker flags for LEVELZERO, overriding pkg-config
  XMKMF       Path to xmkmf, Makefile generator for X Window System
  CPP         C preprocessor
  HWLOC_LIBXML2_CFLAGS
              C compiler flags for LIBXML2, overriding pkg-config
  HWLOC_LIBXML2_LIBS
              linker flags for LIBXML2, overriding pkg-config
  DOXYGEN     Location of the doxygen program (required for building the hwloc
              doxygen documentation)
  PDFLATEX    Location of the pdflatex program (required for building the
              hwloc doxygen documentation)
  MAKEINDEX   Location of the makeindex program (required for building the
              hwloc doxygen documentation)
  FIG2DEV     Location of the fig2dev program (required for building the hwloc
              doxygen documentation)
  GS          Location of the gs program (required for building the hwloc
              doxygen documentation)
  EPSTOPDF    Location of the epstopdf program (required for building the
              hwloc doxygen documentation)
  W3M         Location of the w3m program (required to building the top-level
              hwloc README file)
  LYNX        Location of the lynx program (required to building the top-level
              hwloc README file)
  HWLOC_CAIRO_CFLAGS
              C compiler flags for CAIRO, overriding pkg-config
  HWLOC_CAIRO_LIBS
              linker flags for CAIRO, overriding pkg-config
  DIFF        diff tool
  HWLOC_NUMA_CFLAGS
              C compiler flags for NUMA, overriding pkg-config
  HWLOC_NUMA_LIBS
              linker flags for NUMA, overriding pkg-config

Use these variables to override the choices made by 'configure' or to help
it to find libraries and programs with nonstandard names/locations.

Report bugs to <https://github.com/open-mpi/hwloc/issues>.
*/

