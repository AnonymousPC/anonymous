from module.make import *

configure(
    name="icu",
    file="./package/icu/icu4c/source/configure",
    args=[
        "--disable-icu-config",
        "--enable-debug"    if type == "debug" else "",
        "--disable-release" if type == "debug" else "",
        "--disable-shared",
        "--enable-static",
        "--disable-dyload",
        "--disable-tests",
      # "--disable-tools",
        "--disable-samples"
    ]
)
make(
    name="icu",
    dir="./package/icu/icu4c/source"
)
archieve(
    name="icu",
    libs=[
        "libicudata",
        "libicui18n",
        "libicuio",
        "libicutest",
        "libicutu",
        "libicuuc"
    ]
)

"""
>>> ./package/icu/icu4c/source/configure -h | grep -E 'enable|disable'
      --cache-file=FILE   cache test results in FILE [disabled]
  --disable-option-checking  ignore unrecognized --enable/--with options
  --disable-FEATURE       do not include FEATURE (same as --enable-FEATURE=no)
  --enable-FEATURE[=ARG]  include FEATURE [ARG=yes]
  --disable-icu-config    do not install icu-config
  --enable-debug          build debug libraries and enable the U_DEBUG define
  --disable-release       do not build release libraries
  --disable-strict        do not compile with strict compiler options
  --enable-64bit-libs     (deprecated, use --with-library-bits) build 64-bit libraries default= platform default
  --disable-shared        do not build shared libraries
  --enable-static         build static libraries
  --enable-auto-cleanup   enable auto cleanup of libraries
  --disable-draft         do not enable draft APIs (and internal APIs)
  --disable-renaming      do not add a version suffix to symbols
  --enable-tracing        enable function and data tracing
  --enable-plugins        enable plugins
  --disable-dyload        disable dynamic loading
  --enable-rpath          use rpath when linking default is only if necessary
  --enable-weak-threads   weakly reference the threading library
  --disable-extras        do not build ICU extras
  --disable-icuio         do not build ICU's icuio library
  --enable-layoutex       build ICU's Paragraph Layout library.
  --disable-tools         do not build ICU's tools
  --enable-fuzzer         build ICU's fuzzer test targets
  --disable-tests         do not build ICU tests
  --disable-samples       do not build ICU samples
"""