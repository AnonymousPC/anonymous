#pragma once

template < class context_type >
class asio_context
{
    public: // Core
        asio_context ( )               requires default_initializable<context_type>; // As boost::asio::system_context is not public constructible.
        asio_context ( context_type& );

    public: // Interface
        asio_scheduler<context_type> get_scheduler ( ) noexcept;

    private: // Data
        std::shared_ptr<context_type> ctx_ptr = nullptr;
};

#include "asio_context.ipp"