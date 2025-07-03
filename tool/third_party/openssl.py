from module.make import *

configure(
    module_name="openssl",
    file="./third_party/openssl/Configure",
    args=[
        "no-shared"
    ]
)

make(
    module_name="openssl",
    dir="./third_party/openssl"
)


"""
>>> cat ./third_party/openssl/Configure
...
# Options:
#
# --config      add the given configuration file, which will be read after
#               any "Configurations*" files that are found in the same
#               directory as this script.
# --prefix      prefix for the OpenSSL installation, which includes the
#               directories bin, lib, include, share/man, share/doc/openssl
#               This becomes the value of INSTALLTOP in Makefile
#               (Default: /usr/local)
# --openssldir  OpenSSL data area, such as openssl.cnf, certificates and keys.
#               If it's a relative directory, it will be added on the directory
#               given with --prefix.
#               This becomes the value of OPENSSLDIR in Makefile and in C.
#               (Default: PREFIX/ssl)
# --banner=".." Output specified text instead of default completion banner
#
# -w            Don't wait after showing a Configure warning
#
# --cross-compile-prefix Add specified prefix to binutils components.
#
# --api         One of 0.9.8, 1.0.0, 1.0.1, 1.0.2, 1.1.0, 1.1.1, or 3.0
#               Define the public APIs as they were for that version
#               including patch releases.  If 'no-deprecated' is also
#               given, do not compile support for interfaces deprecated
#               up to and including the specified OpenSSL version.
#
# no-hw-xxx     do not compile support for specific crypto hardware.
#               Generic OpenSSL-style methods relating to this support
#               are always compiled but return NULL if the hardware
#               support isn't compiled.
#
# enable-demos  Enable the building of the example code in the demos directory
# enable-h3demo Enable the http3 demo, which currently only links to the
#               external nghttp3 library on unix platforms
#
# enable-hqinterop
#               Enable the building of the hq-interop code for construction
#               of the interop container
#
# no-hw         do not compile support for any crypto hardware.
# [no-]threads  [don't] try to create a library that is suitable for
#               multithreaded applications (default is "threads" if we
#               know how to do it)
# [no-]thread-pool
#               [don't] allow thread pool functionality
# [no-]default-thread-pool
#               [don't] allow default thread pool functionality
# [no-]shared   [don't] try to create shared libraries when supported.
# [no-]pic      [don't] try to build position independent code when supported.
#               If disabled, it also disables shared and dynamic-engine.
# no-asm        do not use assembler
# no-egd        do not compile support for the entropy-gathering daemon APIs
# [no-]zlib     [don't] compile support for zlib compression.
# zlib-dynamic  Like "zlib", but the zlib library is expected to be a shared
#               library and will be loaded at run-time by the OpenSSL library.
# sctp          include SCTP support
# no-quic       disable QUIC support
# no-uplink     Don't build support for UPLINK interface.
# enable-weak-ssl-ciphers
#               Enable weak ciphers that are disabled by default.
# 386           generate 80386 code in assembly modules
# no-sse2       disables IA-32 SSE2 code in assembly modules, the above
#               mentioned '386' option implies this one
# no-<cipher>   build without specified algorithm (dsa, idea, rc5, ...)
# -<xxx> +<xxx> All options which are unknown to the 'Configure' script are
# /<xxx>        passed through to the compiler. Unix-style options beginning
#               with a '-' or '+' are recognized, as well as Windows-style
#               options beginning with a '/'. If the option contains arguments
#               separated by spaces, then the URL-style notation %20 can be
#               used for the space character in order to avoid having to quote
#               the option. For example, -opt%20arg gets expanded to -opt arg.
#               In fact, any ASCII character can be encoded as %xx using its
#               hexadecimal encoding.
# -static       while -static is also a pass-through compiler option (and
#               as such is limited to environments where it's actually
#               meaningful), it triggers a number configuration options,
#               namely no-pic, no-shared and no-threads. It is
#               argued that the only reason to produce statically linked
#               binaries (and in context it means executables linked with
#               -static flag, and not just executables linked with static
#               libcrypto.a) is to eliminate dependency on specific run-time,
#               a.k.a. libc version. The mentioned config options are meant
#               to achieve just that. Unfortunately on Linux it's impossible
#               to eliminate the dependency completely for openssl executable
#               because of getaddrinfo and gethostbyname calls, which can
#               invoke dynamically loadable library facility anyway to meet
#               the lookup requests. For this reason on Linux statically
#               linked openssl executable has rather debugging value than
#               production quality.
#
# BN_LLONG      use the type 'long long' in crypto/bn/bn.h
# RC4_CHAR      use 'char' instead of 'int' for RC4_INT in crypto/rc4/rc4.h
# Following are set automatically by this script
#
# MD5_ASM       use some extra md5 assembler,
# SHA1_ASM      use some extra sha1 assembler, must define L_ENDIAN for x86
# RMD160_ASM    use some extra ripemd160 assembler,
# SHA256_ASM    sha256_block is implemented in assembler
# SHA512_ASM    sha512_block is implemented in assembler
# AES_ASM       AES_[en|de]crypt is implemented in assembler

# Minimum warning options... any contributions to OpenSSL should at least
# get past these.  Note that we only use these with C compilers, not with
# C++ compilers.

# -DPEDANTIC complements -pedantic and is meant to mask code that
# is not strictly standard-compliant and/or implementation-specific,
# e.g. inline assembly, disregards to alignment requirements, such
# that -pedantic would complain about. Incidentally -DPEDANTIC has
# to be used even in sanitized builds, because sanitizer too is
# supposed to and does take notice of non-standard behaviour. Then
# -pedantic with pre-C9x compiler would also complain about 'long
# long' not being supported. As 64-bit algorithms are common now,
# it grew impossible to resolve this without sizeable additional
# code, so we just tell compiler to be pedantic about everything
# but 'long long' type.
...
"""