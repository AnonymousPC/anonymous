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

template< class executor_type >
class use_sender_t::executor_with_default 
    extends public executor_type 
{
    public: // Typedef
        using default_completion_token_type = boost::asio::use_awaitable_t<>;

    public: // Core
        executor_with_default ( const executor_type& ) noexcept;
        executor_with_default ( const auto& ex ) noexcept 
            requires ( not same_as<decay<decltype(ex)>,executor_with_default> and
                       convertible_to<decay<decltype(ex)>,executor_type> );
};

// class use_sender_t
// {
//     public:
//     constexpr use_sender_t() {}

//     template<class InnerExecutor>
//     struct executor_with_default : InnerExecutor 
//     {
//         using default_completion_token_type = boost::asio::use_awaitable_t<boost::asio::any_io_executor>;

//         executor_with_default(const InnerExecutor& ex)noexcept : InnerExecutor(ex) {}

//         template<class _InnerExecutor>
//             requires (!std::is_same_v<_InnerExecutor, executor_with_default> && std::is_convertible_v<_InnerExecutor, InnerExecutor>)
//         executor_with_default(const _InnerExecutor& ex)noexcept : InnerExecutor(ex) {}
//     };

//     template<class T>
//     using as_default_on_t = typename T::template rebind_executor<
//         executor_with_default<typename T::executor_type>
//     >::other;

//     template<class T>
//     static typename std::decay_t<T>::template rebind_executor<
//         executor_with_default<typename std::decay_t<T>::executor_type>
//     >::other
//         as_default_on(T&& obj) 
//     {
//         return typename std::decay_t<T>::template rebind_executor<
//             executor_with_default<typename std::decay_t<T>::executor_type>
//         >::other(std::forward<T>(obj));
//     }
// };

#include "use_sender.ipp"