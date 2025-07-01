from module.make import *

cmake(
    export_name="xz",
    dir="./third_party/xz",
    args=[
        "-DBUILD_SHARED_LIBS=false",
        "-DXZ_MICROLZMA_ENCODER=false",
        "-DXZ_MICROLSMA_DECODER=false",
        "-DXZ_TOOL_XZDEC=false",
        "-DXZ_TOOL_LZMADEC=false",
        "-DXZ_TOOL_LZMAINFO=false",
        "-DXZ_TOOL_XZ=false",
        "-DXZ_TOOL_SYMLINKS=false",
        "-DXZ_TOOL_SYMLINKS_LZMA=false",
        "-DXZ_TOOL_SCRIPTS=false",
        "-DXZ_DOXYGEN=false",
        "-DXZ_DOC=false"
    ]
)


"""
>>> cat ./third_party/xz/CMakeLists.txt | grep option\\(
    option(XZ_ASM_I386 "Enable 32-bit x86 assembly code"
option(XZ_NLS "Native Language Support (translated messages and man pages)"
option(BUILD_SHARED_LIBS "Build liblzma as a shared library instead of static")
option(XZ_SMALL "Reduce code size at expense of speed. \
option(XZ_EXTERNAL_SHA256 "Use SHA-256 code from the operating system \
option(XZ_MICROLZMA_ENCODER
option(XZ_MICROLZMA_DECODER
option(XZ_LZIP_DECODER "Support lzip decoder" ON)
    option(XZ_CLMUL_CRC "Use carryless multiplication for CRC \
option(XZ_ARM64_CRC32 "Use ARM64 CRC32 instructions (with runtime detection) \
option(XZ_LOONGARCH_CRC32
option(XZ_TOOL_XZDEC "Build and install the xzdec command line tool" ON)
option(XZ_TOOL_LZMADEC "Build and install the lzmadec command line tool" ON)
option(XZ_TOOL_LZMAINFO "Build and install the lzmainfo command line tool" ON)
option(XZ_TOOL_XZ "Build and install the xz command line tool" ON)
        option(XZ_TOOL_SYMLINKS "Create unxz and xzcat symlinks" ON)
        option(XZ_TOOL_SYMLINKS_LZMA
    option(XZ_TOOL_SCRIPTS "Install the scripts \
    option(XZ_DOXYGEN "Use Doxygen to generate liblzma API docs" OFF)
option(XZ_DOC "Install basic documentation, examples, and license files" ON)
"""