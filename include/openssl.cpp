module;
#undef in
#include <openssl/crypto.h>
inline namespace __openssl_magic__
{
    struct OPENSSL_malloc_cpp
    {
        void* ptr = nullptr;
        constexpr OPENSSL_malloc_cpp (auto num) extends ptr ( OPENSSL_malloc(num) ) { }
        template < class type > constexpr operator type* ( ) const { return static_cast<type*>(ptr); }
    };
    struct OPENSSL_zalloc_cpp
    {
        void* ptr = nullptr;
        constexpr OPENSSL_zalloc_cpp (auto num) extends ptr ( OPENSSL_zalloc(num) ) { }
        template < class type > constexpr operator type* ( ) const { return static_cast<type*>(ptr); }
    };
    struct OPENSSL_realloc_cpp
    {
        void* ptr = nullptr;
        constexpr OPENSSL_realloc_cpp (auto addr, auto num) extends ptr ( OPENSSL_realloc(addr, num) ) { }
        template < class type > constexpr operator type* ( ) const { return static_cast<type*>(ptr); }
    };
    struct OPENSSL_memdup_cpp
    {
        void* ptr = nullptr;
        constexpr OPENSSL_memdup_cpp (auto str, auto s) extends ptr ( OPENSSL_memdup(str, s) ) { }
        template < class type > constexpr operator type* ( ) const { return static_cast<type*>(ptr); }
    };
}
#undef  OPENSSL_malloc
#define OPENSSL_malloc  OPENSSL_malloc_cpp
#undef  OPENSSL_zalloc
#define OPENSSL_zalloc  OPENSSL_zalloc_cpp
#undef  OPENSSL_realloc
#define OPENSSL_realloc OPENSSL_realloc_cpp
#undef  OPENSSL_memdup
#define OPENSSL_memdup  OPENSSL_memdup_cpp
#ifndef OPENSSL_SYS_VMS
    #include <unistd.h>
#endif
#include <crypto/bio/bio_lib.c>
inline namespace __openssl_magic__
{
    struct BIO_get_data_cpp
    {
        void* ptr = nullptr;
        constexpr BIO_get_data_cpp (auto a) extends ptr ( BIO_get_data(a) ) { }
        template < class type > constexpr operator type* ( ) const { return static_cast<type*>(ptr); }
    };
}
#define BIO_get_data BIO_get_data_cpp
#include <openssl/ssl.h>
#include <ssl/bio_ssl.c>
#include <ssl/d1_lib.c>
#include <ssl/d1_msg.c>
#include <ssl/d1_srtp.c>
#include <ssl/methods.c>
#include <ssl/pqueue.c>
#include <ssl/priority_queue.c>
#include <ssl/quic/cc_newreno.c>
#include <ssl/quic/json_enc.c>
#include <ssl/quic/qlog_event_helpers.c>
#include <ssl/quic/qlog.c>
#include <ssl/quic/quic_ackm.c>
#include <ssl/quic/quic_cfq.c>
#include <ssl/quic/quic_channel.c>
#include <ssl/quic/quic_demux.c>
#include <ssl/quic/quic_engine.c>
#include <ssl/quic/quic_fc.c>
#include <ssl/quic/quic_fifd.c>
#include <ssl/quic/quic_impl.c>
#include <ssl/quic/quic_lcidm.c>
#include <ssl/quic/quic_method.c>
#include <ssl/quic/quic_obj.c>
#include <ssl/quic/quic_port.c>
#include <ssl/quic/quic_rcidm.c>
#include <ssl/quic/quic_reactor_wait_ctx.c>
#include <ssl/quic/quic_reactor.c>
#include <ssl/quic/quic_record_rx.c>
#include <ssl/quic/quic_record_shared.c>
#include <ssl/quic/quic_record_tx.c>
#include <ssl/quic/quic_record_util.c>
#include <ssl/quic/quic_rstream.c>
#include <ssl/quic/quic_rx_depack.c>
#include <ssl/quic/quic_sf_list.c>
#include <ssl/quic/quic_srt_gen.c>
#include <ssl/quic/quic_srtm.c>
#include <ssl/quic/quic_sstream.c>
#include <ssl/quic/quic_statm.c>
#include <ssl/quic/quic_stream_map.c>
#include <ssl/quic/quic_thread_assist.c>
#include <ssl/quic/quic_tls_api.c>
#include <ssl/quic/quic_tls.c>
#include <ssl/quic/quic_trace.c>
#include <ssl/quic/quic_tserver.c>
#include <ssl/quic/quic_txp.c>
#include <ssl/quic/quic_txpim.c>
#include <ssl/quic/quic_types.c>
#include <ssl/quic/quic_wire_pkt.c>
#include <ssl/quic/quic_wire.c>
#include <ssl/quic/uint_set.c>
#include <ssl/record/methods/dtls_meth.c>
#include <ssl/record/methods/ktls_meth.c>
#include <ssl/record/methods/ssl3_cbc.c>
#include <ssl/record/methods/ssl3_meth.c>
#include <ssl/record/methods/tls_common.c>
#include <ssl/record/methods/tls_multib.c>
#include <ssl/record/methods/tls_pad.c>
#include <ssl/record/methods/tls1_meth.c>
#include <ssl/record/methods/tls13_meth.c>
#include <ssl/record/methods/tlsany_meth.c>
#include <ssl/record/rec_layer_d1.c>
#include <ssl/record/rec_layer_s3.c>
#include <ssl/rio/poll_builder.c>
#include <ssl/rio/poll_immediate.c>
#include <ssl/rio/rio_notifier.c>
#include <ssl/s3_enc.c>
#include <ssl/s3_lib.c>
#include <ssl/s3_msg.c>
#include <ssl/ssl_asn1.c>
#include <ssl/ssl_cert_comp.c>
#include <ssl/ssl_cert.c>
#include <ssl/ssl_ciph.c>
#include <ssl/ssl_conf.c>
#include <ssl/ssl_err_legacy.c>
#include <ssl/ssl_init.c>
#include <ssl/ssl_lib.c>
#include <ssl/ssl_mcnf.c>
#include <ssl/ssl_rsa_legacy.c>
#include <ssl/ssl_rsa.c>
#include <ssl/ssl_sess.c>
#include <ssl/ssl_stat.c>
#include <ssl/ssl_txt.c>
#include <ssl/ssl_utst.c>
#include <ssl/statem/extensions_clnt.c>
#include <ssl/statem/extensions_cust.c>
#include <ssl/statem/extensions_srvr.c>
#include <ssl/statem/extensions.c>
#include <ssl/statem/statem_clnt.c>
#include <ssl/statem/statem_dtls.c>
#include <ssl/statem/statem_lib.c>
#include <ssl/statem/statem_srvr.c>
#include <ssl/statem/statem.c>
#include <ssl/t1_enc.c>
#include <ssl/t1_lib.c>
#include <ssl/t1_trce.c>
#include <ssl/tls_depr.c>
#include <ssl/tls_srp.c>
#include <ssl/tls13_enc.c>

export module openssl;

export
{
    using ::SSL_read;
    using ::SSL_write;
}