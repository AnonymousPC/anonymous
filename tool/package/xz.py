from module.make import *

cmake(
    name="xz",
    dir="./package/xz",
    args=[
        "-DBUILD_SHARED_LIBS=false",
        "-DXZ_MICROLZMA_ENCODER=false",
        "-DXZ_MICROLZMA_DECODER=false",
        "-DXZ_TOOL_XZDEC=false",
        "-DXZ_TOOL_LZMADEC=false",
        "-DXZ_TOOL_LZMAINFO=false",
        "-DXZ_TOOL_XZ=false",
        "-DXZ_TOOL_SCRIPTS=false",
        "-DXZ_DOXYGEN=false",
        "-DXZ_DOC=false"
    ]
)
archieve(
    name="xz",
    libs=["liblzma"]
)

"""
>>> cat ./package/xz/CMakeLists.txt | grep option
#     With empty CMAKE_BUILD_TYPE, the -UNDEBUG option will go
#     after the -DNDEBUG option on the compiler command line and
# option with find_package() to avoid a conflict with the FindLibLZMA module
    # entries where "-O3" would appear as part of some other option,
# aren't needed, those are optional in C11/C17). C11 is preferred since C11
# features may be optionally used if they are available.
# in "XZx20Utils" in the compiled binary. The option --use-temp-file
# the /MANIFEST:NO option, other manifest-related linker flags are
    option(XZ_ASM_I386 "Enable 32-bit x86 assembly code"
option(XZ_NLS "Native Language Support (translated messages and man pages)"
# Add warning options for GCC or Clang. Keep this in sync with configure.ac.
# NOTE: add_compile_options() doesn't affect the feature checks;
            add_compile_options("${OPT}")
option(BUILD_SHARED_LIBS "Build liblzma as a shared library instead of static")
    # The XZ_SYMBOL_VERSIONING option is ignored for static libraries but
    # we keep the option visible still in case the project is reconfigured
        # the default. The opposite option --undefined-version was only added
option(XZ_SMALL "Reduce code size at expense of speed. \
option(XZ_EXTERNAL_SHA256 "Use SHA-256 code from the operating system \
option(XZ_MICROLZMA_ENCODER
option(XZ_MICROLZMA_DECODER
option(XZ_LZIP_DECODER "Support lzip decoder" ON)
    option(XZ_CLMUL_CRC "Use carryless multiplication for CRC \
option(XZ_ARM64_CRC32 "Use ARM64 CRC32 instructions (with runtime detection) \
        # sysctlbyname("hw.optional.armv8_crc32", ...) is supported on Darwin
        # sysctlbyname("hw.optional.armv8_crc32", ...).
option(XZ_LOONGARCH_CRC32
# option -fvisibility=hidden (or equivalent) if and only if it is supported.
# or such option so HAVE_VISIBILITY should be 1 only when both option and
# command line option for visibility support. It's empty or unset when
            target_link_options(liblzma PRIVATE
    # Note that adding link options doesn't affect static builds
        target_link_options(liblzma PRIVATE "-Wl,--undefined-version")
    target_link_options(liblzma PRIVATE
        target_link_options(liblzma PRIVATE "-Wl,--undefined-version")
    target_link_options(liblzma PRIVATE
# behavior between operating systems. This optionally includes a dependency
# and optionally its alternative names as symlinks. This is a helper function
# Installs a man page file and optionally its alternative names as symlinks.
option(XZ_TOOL_XZDEC "Build and install the xzdec command line tool" ON)
option(XZ_TOOL_LZMADEC "Build and install the lzmadec command line tool" ON)
option(XZ_TOOL_LZMAINFO "Build and install the lzmainfo command line tool" ON)
option(XZ_TOOL_XZ "Build and install the xz command line tool" ON)
        src/xz/options.c
        src/xz/options.h
    #   - MSYS2 supports the same winsymlinks option in the environment
        option(XZ_TOOL_SYMLINKS "Create unxz and xzcat symlinks" ON)
        option(XZ_TOOL_SYMLINKS_LZMA
        # Install the man pages and (optionally) their symlinks
    option(XZ_TOOL_SCRIPTS "Install the scripts \
    # has a separate option --enable-path-for-scripts=PREFIX but this is
    option(XZ_DOXYGEN "Use Doxygen to generate liblzma API docs" OFF)
option(XZ_DOC "Install basic documentation, examples, and license files" ON)
"""