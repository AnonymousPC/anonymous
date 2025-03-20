#pragma once

class use_sender_t
{
    public: // Core
        constexpr use_sender_t ( ) = default;

    public: // Typedef
        template < class executor_type >
        class executor_with_default;

        template < class context_type >
        using as_default_on_t = context_type::template rebind_executor<executor_with_default<typename context_type::executor_type>>::other;

    public: // Member
        static auto as_default_on ( auto&& );
};

#include "use_sender.ipp"