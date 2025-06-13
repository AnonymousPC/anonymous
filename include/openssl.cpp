module;
#undef in
#include <openssl/ssl.h>

export module openssl
#ifdef _WIN32
    [[anonymous::perl_configure("lib/git/openssl/Configure")]]
    [[anonymous::fixme, nmake]]
#elif defined(__linux__) or defined(__MACH__)
    [[anonymous::perl_configure("lib/git/openssl/Configure")]]
    [[anonymous::make_directory("lib/git/openssl"          )]]
    [[anonymous::update_header ("<openssl/asn1.h>"         )]]
    [[anonymous::update_header ("<openssl/bio.h>"          )]]
    [[anonymous::update_header ("<openssl/conf.h>"         )]]
    [[anonymous::update_header ("<openssl/configuration.h>")]]
    [[anonymous::update_header ("<openssl/comp.h>"         )]]
    [[anonymous::update_header ("<openssl/ct.h>"           )]]
    [[anonymous::update_header ("<openssl/crypto.h>"       )]]
    [[anonymous::update_header ("<openssl/lhash.h>"        )]]
    [[anonymous::update_header ("<openssl/opensslv.h>"     )]]
    [[anonymous::update_header ("<openssl/pkcs7.h>"        )]]
    [[anonymous::update_header ("<openssl/safestack.h>"    )]]
    [[anonymous::update_header ("<openssl/ssl.h>"          )]]
    [[anonymous::update_header ("<openssl/x509.h>"         )]]
    [[anonymous::update_header ("<openssl/x509_vfy.h>"     )]]
    [[anonymous::update_library("libssl"                   )]]
    [[anonymous::update_library("libcrypto"                )]];
#endif