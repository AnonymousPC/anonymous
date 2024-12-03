#pragma once

template < class collection_type, class iterate_type >
class collection_algo
{
    private: // Abbreviation
        constexpr int            size  ( ) const;
        constexpr bool           empty ( ) const;
        constexpr decltype(auto) begin ( );
        constexpr decltype(auto) begin ( ) const;
        constexpr decltype(auto) end   ( );
        constexpr decltype(auto) end   ( ) const;

    public: // Algorithm
        constexpr       bool             all     ( unary_pred    <iterate_type>  auto ) const;
        constexpr       int              count   ( unary_pred    <iterate_type>  auto ) const;
        constexpr       bool             exist   ( unary_pred    <iterate_type>  auto ) const;
        constexpr       bool             none    ( unary_pred    <iterate_type>  auto ) const;

        constexpr       collection_type& each    ( std::invocable<iterate_type&> auto );
        constexpr const collection_type& each    ( std::invocable<iterate_type>  auto ) const;

        constexpr       auto             sum     (                                       ) const requires std::default_initializable<iterate_type>                             and addable<iterate_type>;
        constexpr       auto             sum     ( std::invocable<iterate_type>  auto op ) const requires std::default_initializable<invoke_result<decltype(op),iterate_type>> and addable<invoke_result<decltype(op),iterate_type>>;
        constexpr       auto             product (                                       ) const requires std::convertible_to<int,iterate_type>                                and multipliable<iterate_type>;
        constexpr       auto             product ( std::invocable<iterate_type>  auto op ) const requires std::convertible_to<int,invoke_result<decltype(op),iterate_type>>    and multipliable<invoke_result<decltype(op),iterate_type>>;
};


#include "collection_algo.ipp"