from module.make import *

cmake(
    module_name="bzip2",
    dir="./third_party/bzip2",
    args=[
        "-DENABLE_WERROR=false",
       f"-DENABLE_DEBUG={type=='debug'}",
        "-DENABLE_APP=false",
        "-DENABLE_TESTS=false",
        "-DENABLE_DOCS=false",
        "-DENABLE_EXAMPLES=false",
        "-DENABLE_LIB_ONLY=true",
        "-DENABLE_STATIC_LIB=true",
        "-DENABLE_SHARED_LIB=false"
    ]
)

"""
>>> cat ./third_party/bzip2/CMakeOptions.txt | grep option
option(ENABLE_WERROR     "Turn on compile time warnings")
option(ENABLE_DEBUG      "Turn on debug output")
option(ENABLE_APP        "Build applications (bzip2, and bzip2recover)"
option(ENABLE_TESTS      "Build/enable unit tests."
option(ENABLE_DOCS       "Generate documentation"
option(ENABLE_EXAMPLES   "Build examples"
option(ENABLE_LIB_ONLY   "Build libbz2 only.  This is a short hand for -DENABLE_APP=0 -DENABLE_EXAMPLES=0")
option(ENABLE_STATIC_LIB "Build libbz2 in static mode also")
option(ENABLE_SHARED_LIB "Build libbz2 as a shared library" ON)
option(USE_OLD_SONAME "Use libbz2.so.1.0 for compatibility with old Makefiles" OFF)
option(ENABLE_STATIC_LIB_IS_PIC "Enable position independent code for the static library" ON)
"""
