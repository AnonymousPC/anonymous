#pragma once

extern boost::asio::ssl::context ssl_context;
extern boost::asio::ssl::context tls_context;

#include "global.ipp"
#if dll
    #include "global.cpp"
#endif