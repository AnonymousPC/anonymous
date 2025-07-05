from module.make import *

configure(
    name="openssl",
    file="./package/openssl/Configure",
    args=[
        "no-apps",
        "no-engine",
        "no-docs",
        "no-legacy",
        "no-module",
        "no-shared",
        "zlib"
    ]
)
make(
    name="openssl",
    dir="./package/openssl",
)
archieve(
    name="openssl",
    libs=[
        "libssl",
        "libcrypto"
    ]
)


"""
>>> /* git clone openssl && cd openssl && */ mkdir build && cd build && ../Configure && perl configdata.pm --dump
...
Enabled features:

    apps
    argon2
    aria
    asm
    async
    atexit
    autoalginit
    autoerrinit
    autoload-config
    bf
    blake2
    bulk
    cached-fetch
    camellia
    capieng
    cast
    chacha
    cmac
    cmp
    cms
    comp
    ct
    default-thread-pool
    deprecated
    des
    dgram
    dh
    docs
    dsa
    dso
    dtls
    dynamic-engine
    ec
    ec2m
    ecdh
    ecdsa
    ecx
    engine
    err
    filenames
    gost
    http
    idea
    integrity-only-ciphers
    legacy
    loadereng
    makedepend
    md4
    mdc2
    ml-dsa
    ml-kem
    module
    multiblock
    nextprotoneg
    ocb
    ocsp
    padlockeng
    pic
    pinshared
    poly1305
    posix-io
    psk
    quic
    unstable-qlog
    rc2
    rc4
    rdrand
    rfc3779
    rmd160
    scrypt
    secure-memory
    seed
    shared
    siphash
    siv
    slh-dsa
    sm2
    sm2-precomp
    sm3
    sm4
    sock
    srp
    srtp
    sse2
    ssl
    ssl-trace
    static-engine
    stdio
    tests
    thread-pool
    threads
    tls
    tls-deprecated-ec
    ts
    ui-console
    whirlpool
    tls1
    tls1-method
    tls1_1
    tls1_1-method
    tls1_2
    tls1_2-method
    tls1_3
    dtls1
    dtls1-method
    dtls1_2
    dtls1_2-method

Disabled features:

    acvp-tests             [cascade]        OPENSSL_NO_ACVP_TESTS
    afalgeng               [not-linux]      OPENSSL_NO_AFALGENG
    asan                   [default]        OPENSSL_NO_ASAN
    brotli                 [default]        OPENSSL_NO_BROTLI
    brotli-dynamic         [default]        OPENSSL_NO_BROTLI_DYNAMIC
    buildtest-c++          [default]        
    winstore               [not-windows]    OPENSSL_NO_WINSTORE
    crypto-mdebug          [default]        OPENSSL_NO_CRYPTO_MDEBUG
    demos                  [default]        OPENSSL_NO_DEMOS
    h3demo                 [default]        OPENSSL_NO_H3DEMO
    hqinterop              [default]        OPENSSL_NO_HQINTEROP
    devcryptoeng           [default]        OPENSSL_NO_DEVCRYPTOENG
    ec_nistp_64_gcc_128    [default]        OPENSSL_NO_EC_NISTP_64_GCC_128
    egd                    [default]        OPENSSL_NO_EGD
    external-tests         [default]        OPENSSL_NO_EXTERNAL_TESTS
    fips                   [default]        
    fips-securitychecks    [cascade]        OPENSSL_NO_FIPS_SECURITYCHECKS
    fips-post              [cascade]        OPENSSL_NO_FIPS_POST
    fips-jitter            [default]        OPENSSL_NO_FIPS_JITTER
    fuzz-afl               [default]        OPENSSL_NO_FUZZ_AFL
    fuzz-libfuzzer         [default]        OPENSSL_NO_FUZZ_LIBFUZZER
    jitter                 [default]        OPENSSL_NO_JITTER
    ktls                   [default]        OPENSSL_NO_KTLS
    md2                    [default]        OPENSSL_NO_MD2 (skip crypto/md2)
    msan                   [default]        OPENSSL_NO_MSAN
    pie                    [default]        OPENSSL_NO_PIE
    rc5                    [default]        OPENSSL_NO_RC5 (skip crypto/rc5)
    sctp                   [default]        OPENSSL_NO_SCTP
    sslkeylog              [default]        OPENSSL_NO_SSLKEYLOG
    tfo                    [default]        OPENSSL_NO_TFO
    trace                  [default]        OPENSSL_NO_TRACE
    ubsan                  [default]        OPENSSL_NO_UBSAN
    unit-test              [default]        OPENSSL_NO_UNIT_TEST
    uplink                 [no uplink_arch] OPENSSL_NO_UPLINK
    weak-ssl-ciphers       [default]        OPENSSL_NO_WEAK_SSL_CIPHERS
    zlib                   [default]        OPENSSL_NO_ZLIB
    zlib-dynamic           [default]        OPENSSL_NO_ZLIB_DYNAMIC
    zstd                   [default]        OPENSSL_NO_ZSTD
    zstd-dynamic           [default]        OPENSSL_NO_ZSTD_DYNAMIC
    ssl3                   [default]        OPENSSL_NO_SSL3
    ssl3-method            [default]        OPENSSL_NO_SSL3_METHOD
...
"""