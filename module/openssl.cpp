#if defined(__GNUC__) and not defined(__clang__)
    #pragma GCC diagnostic ignored "-Wunknown-pragmas"
#elifdef __clang__
    #pragma clang diagnostic ignored "-Wunknown-pragmas"
#elif defined(_MSC_VER) and not defined(__clang__)
    #warning "not coded yet"
#endif

/* DEPENDS ON ZLIB, ...*/

#ifdef _WIN32
    #warning "not coded yet"
#elif defined(__linux__) or defined(__MACH__)
    #pragma build "mkdir -p {os.getcwd()}/bin/{type}/cmake/openssl-build"
    #pragma build "cd   {os.getcwd()}/bin/{type}/cmake/openssl-build"
    #pragma build "perl $annonymous/third_party/git/openssl/Configure"
#endif

module;
#undef in
#include <openssl/ssl.h>

export module openssl;
import zlib;
    [[anonymous::perl_file     ("third_party/git/openssl/Configure")]]
    [[anonymous::make_directory("third_party/git/openssl"          )]]
    [[anonymous::update_header ("<openssl/asn1.h>"                 )]]
    [[anonymous::update_header ("<openssl/bio.h>"                  )]]
    [[anonymous::update_header ("<openssl/conf.h>"                 )]]
    [[anonymous::update_header ("<openssl/configuration.h>"        )]]
    [[anonymous::update_header ("<openssl/comp.h>"                 )]]
    [[anonymous::update_header ("<openssl/ct.h>"                   )]]
    [[anonymous::update_header ("<openssl/crypto.h>"               )]]
    [[anonymous::update_header ("<openssl/err.h>"                  )]]
    [[anonymous::update_header ("<openssl/lhash.h>"                )]]
    [[anonymous::update_header ("<openssl/opensslv.h>"             )]]
    [[anonymous::update_header ("<openssl/pkcs7.h>"                )]]
    [[anonymous::update_header ("<openssl/safestack.h>"            )]]
    [[anonymous::update_header ("<openssl/ssl.h>"                  )]]
    [[anonymous::update_header ("<openssl/ui.h>"                   )]]
    [[anonymous::update_header ("<openssl/x509.h>"                 )]]
    [[anonymous::update_header ("<openssl/x509v3.h>"               )]]
    [[anonymous::update_header ("<openssl/x509_vfy.h>"             )]]
    [[anonymous::update_library("libssl"                           )]]
    [[anonymous::update_library("libcrypto"                        )]];
