#pragma once

template < layer_type... types >
class sequence_model
    extends public tuple<types...>
{
    private: // Precondition
        static_assert ( aux::chain_invocable<types...> );

    public: // Interface
        constexpr array_type auto forward  ( const array_type auto& );
        constexpr array_type auto forward  (       array_type auto,  optimizer_type auto& );
        constexpr            void backward ( const loss_type  auto&, optimizer_type auto& );

    private: // Auxiliary
        template < int index = 1 >                constexpr auto tuplewise_forward  ( const auto& )        const;
        template < int index = 1 >                constexpr auto tuplewise_forward  (       auto,  auto& ) const;
        template < int index = sizeof...(types) > constexpr void tuplewise_backward ( const auto&, auto& );
};

#include "sequence_model.ipp"