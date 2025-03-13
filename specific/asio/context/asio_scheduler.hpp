#pragma once

template < class context_type >
class asio_scheduler
{
    public: // Data
        context_type& ctx;

    public: // Interface
        auto schedule ( ) const noexcept;

    public: // Operator
        friend bool operator == ( const asio_scheduler&, const asio_scheduler& ) noexcept = default;

    private: // Typedef
        class sender;
};

#include "asio_scheduler.ipp"